
///====================================================================
/// 前方宣言用
///====================================================================

/* -- DirectXObject --*/ 
#include"DirectX/DirectXobject/DXGI.h"
#include"DirectX/DirectXobject/Device.h"
#include"DirectX/DirectXobject/CommandQueue.h"
#include"DirectX/DirectXobject/CommandAllocator.h"
#include"DirectX/DirectXobject/GraphicsCommandList.h"
#include"DirectX/DirectXobject/DescriptorHeap.h"
#include"DirectX/DirectXobject/SwapChain.h"
#include"DirectX/DirectXobject/RenderTarget.h"
#include"DirectX/DirectXobject/Fence.h"

/* -- 各Factory -- */
#include"DirectX/GraphicsCommandObjectFactory.h"
#include"DirectX/StaticHeapContainer.h"


#include"DirectX/ResourceBarrierHelper.h"

///====================================================================

#include"DirectXRenderer.h"

#include"../Debug/DebugLogSystem.h"

///====================================================================

DirectXRenderer::DirectXRenderer() = default;
DirectXRenderer::~DirectXRenderer() = default;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== 描画機能作成関数 ===
//@param	window	ウィンドウインターフェース
//@details	作成したウィンドウに描画するため引数で参照を渡す
//@return	作成の成否
[[nodiscard]] bool DirectXRenderer::create_renderer(windowInterface* window) {

	auto hwnd = (HWND)window->get_native_handle();
	auto window_size = window->get_window_size();
	frame_index_value.resize(frame_resouse_size, 0);

	//	DXGIインスタンス生成
	dxgi_ = std::make_unique<DXGI>();
	if (FAILED(dxgi_->initialize_DXGI())) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//	Deviceインスタンス生成
	device_ = std::make_unique<Device>();
	if (FAILED(device_->initialize_Device(dxgi_->get_DXGI_adaptor()))) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//	描画用コマンドオブジェクト構造体インスタンス生成
	graphics_command_object = std::make_unique<GraphicsCommandObject>(frame_resouse_size);
	if (FAILED(GraphicsCommandObjectFactory::create_GraphicsCommandObject(device_->get_device(), *graphics_command_object))) {
		DEBUG_LOG("DirectXRenderer :: create_GraphicsCommandObject() FAILED");
		return false;
	}
	
	//	初期作成ディスクリプタヒープコンテナインスタンス生成
	static_heap_container = std::make_unique<StaticHeapContainer>();
	if (FAILED(static_heap_container->create_static_heap_container(device_->get_device(),
		{
			{D3D12_DESCRIPTOR_HEAP_TYPE_RTV,buffer_size,D3D12_DESCRIPTOR_HEAP_FLAG_NONE},//RTV
		}
	))) {
		DEBUG_LOG("DirectXRenderer :: create_static_heap_container() FAILED");
		return false;
	}

	//	スワップチェーンインスタンス生成
	swap_chain = std::make_unique<SwapChain>();
	if (FAILED(swap_chain->create_swapchain(dxgi_->get_DXGI_factory(),graphics_command_object->queue_->get_command_queue(), 
		window_size, hwnd, buffer_size))) {
		DEBUG_LOG("DirectXRenderer :: create_swapchain() FAILED");
		return false;
	}

	//	最終描画先レンダーターゲットインスタンス生成
	render_targets.resize(buffer_size);
	for (unsigned int i = 0; i < buffer_size; i++) {

		auto& p = render_targets[i];
		p = std::make_unique<RenderTarget>();
		if (FAILED(p->create_render_target(device_->get_device(), swap_chain->get_swapchain(),
			static_heap_container->get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)->get_cpu_descriptor_handle(i), i))) {
			DEBUG_LOG("DirectXRenderer :: create_swapchain() FAILED");
			return false;
		}
	}

	//	Fenceインスタンス生成
	fence_ = std::make_unique<Fence>();
	if (FAILED(fence_->create_fence(device_->get_device()))) {
		DEBUG_LOG("DirectXRenderer :: create_fence() FAILED");
		return false;
	}

	DEBUG_LOG("DirectXRenderer :: create_renderer() SUCCESS");
	return true;
}

///====================================================================
/// 実行時処理関数群
///====================================================================

/* -- 描画制御 -- */

//@brief	=== 描画更新関数 ===
//@details	毎フレーム更新される想定
void DirectXRenderer::update_renderer() {

	/* -- 更新前処理 -- */
	begin_update_renderer();

	sync_frame_resource();

	/* -- 描画機能更新 -- */

	//	描画先のバッファインデックスを取得
	const auto backBufferIndex = swap_chain->get_swapchain()->GetCurrentBackBufferIndex();

	//	描画用コマンドオブジェクト分解取得
	auto queue = graphics_command_object->queue_.get();
	auto allocator = graphics_command_object->allocators_[current_frame_index].get();
	auto list_ins = graphics_command_object->list_.get();

	// コマンドアロケータリセット
	allocator->reset_command_allocator();
	// コマンドリストリセット
	list_ins->reset_command_list(allocator->get_command_allocator());

	auto* list = list_ins->get_graphics_command_list();

	auto target = render_targets[backBufferIndex].get();

	// リソースバリアでレンダーターゲットを Present から RenderTarget へ変更
	auto pToRT = ResourceBarrierHelper::create_resource_barrier(target->get_render_target(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	list->ResourceBarrier(1, &pToRT);

	// レンダーターゲットの設定
	D3D12_CPU_DESCRIPTOR_HANDLE handles[] = { target->get_rtv_handle() };
	list->OMSetRenderTargets(1, handles, false, nullptr);

	// レンダーターゲットのクリア
	const float clearColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	list->ClearRenderTargetView(handles[0], clearColor, 0, nullptr);

	// リソースバリアでレンダーターゲットを RenderTarget から Present へ変更
	auto rtToP = ResourceBarrierHelper::create_resource_barrier(target->get_render_target(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	list->ResourceBarrier(1, &rtToP);

	// コマンドリストをクローズ
	list->Close();

	// コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { list };
	queue->get_command_queue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// プレゼント
	swap_chain->get_swapchain()->Present(1, 0);

	/* -- 更新後処理 -- */
	end_update_renderer();
}

//@brief	=== 描画更新前関数 ===
//@details	描画機能を更新する際に先に処理する必要があるものを呼び出す関数
void DirectXRenderer::begin_update_renderer() {

	frame_count++;
}

//@brief	=== 描画更新後関数 ===
//@details	描画機能を更新した後に処理する必要があるものを呼び出す関数
void DirectXRenderer::end_update_renderer() {

	//	シグナルを送って配列に保存
	frame_index_value[current_frame_index] = fence_->signal(graphics_command_object->queue_->get_command_queue());

	//	フレームリソースサイクルを進める
	current_frame_index = (current_frame_index + 1) % frame_resouse_size;
}

//@brief == = フレームリソース使用可能確認関数 == =
//@details	フレームリソースが使用可能な状態か確認する関数
void DirectXRenderer::sync_frame_resource() {

	//	これから使うフレームリソースが使える状態か判断
	if (frame_index_value[current_frame_index] > fence_->get_completed_value()) {
		fence_->wait_to_completed_value(frame_index_value[current_frame_index]);
	}
}

///====================================================================
/// 終了時処理関数
///====================================================================

//@brief	=== 描画機能終了処理関数 ===
//@details	描画機能破棄前最終処理(非同期処理の待機など)をするための関数
void DirectXRenderer::end_renderer() {

	//	すべてのフレームリソースが使われなくなるまで待機
	for (auto& value : frame_index_value) {
		fence_->wait_to_completed_value(value);
	}

	DEBUG_LOG("DirectXRenderer :: end_renderer()");
	DEBUG_LOG("DirectXRenderer :: frame_count = ", frame_count);
}