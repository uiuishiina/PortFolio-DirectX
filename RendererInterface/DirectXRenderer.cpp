
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

#include"DirectX/FrameResource.h"

/* -- 各Factory -- */
#include"DirectX/CommandObjectFactory.h"
#include"DirectX/FrameResourceFactory.h"

#include"DirectX/StaticHeapContainer.h"


#include"DirectX/ResourceBarrierHelper.h"

///====================================================================

#include<chrono>

#include"DirectXRenderer.h"

#include"../Debug/DebugLogSystem.h"

namespace {
	const bool create_timer_flag = true;
	const bool update_timer_flag = false;
}

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

	auto start = std::chrono::high_resolution_clock::now();

	auto hwnd = (HWND)window->get_native_handle();
	auto window_size = window->get_window_size();
	
	frame_resources.resize(frame_resouse_size);

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

	//	描画用コマンドキューインスタンス生成
	graphics_queue = std::make_unique<CommandQueue>();
	if (FAILED(CommandObjectFactory::create_graphics_command_queue(device_->get_device(),*graphics_queue))) {
		DEBUG_LOG("DirectXRenderer :: create_command_queue() FAILED");
		return false;
	}

	//	フレームリソース生成
	if (FAILED(FrameResourceFactory::create_frame_resources(device_->get_device(), frame_resouse_size, frame_resources))) {
		DEBUG_LOG("DirectXRenderer :: create_frame_resources() FAILED");
		return false;
	}

	//	描画用コマンドリストインスタンス生成
	graphics_list = std::make_unique<GraphicsCommandList>();
	if (FAILED(CommandObjectFactory::create_graphics_command_list(device_->get_device(), 
		frame_resources[0]->get_graphics_allocator()->get_command_allocator(), *graphics_list))) {
		DEBUG_LOG("DirectXRenderer :: create_command_queue() FAILED");
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
	if (FAILED(swap_chain->create_swapchain(dxgi_->get_DXGI_factory(), graphics_queue->get_command_queue(),
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

	auto end = std::chrono::high_resolution_clock::now();

	if (create_timer_flag) {
		DEBUG_LOG("create_renderer end = ", std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()),"us");
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
	
	auto start = std::chrono::high_resolution_clock::now();

	/* -- 更新前処理 -- */

	// 外部との連携
	begin_update_renderer();

	//	リソース待機
	sync_frame_resource();

	/* -- 描画機能更新 -- */

	//	描画先のバッファインデックスを取得
	const auto backBufferIndex = swap_chain->get_swapchain()->GetCurrentBackBufferIndex();

	//	参照を保存
	auto* queue = graphics_queue->get_command_queue();
	auto* list = graphics_list->get_graphics_command_list();
	auto* allocator = frame_resources[current_frame_index]->get_graphics_allocator();

	// コマンドアロケータリセット
	allocator->reset_command_allocator();
	// コマンドリストリセット
	graphics_list->reset_command_list(allocator->get_command_allocator());

	auto target = render_targets[backBufferIndex].get();

	// リソースバリアでレンダーターゲットを Present から RenderTarget へ変更
	auto pToRT = ResourceBarrierHelper::create_resource_barrier(target->get_render_target(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	list->ResourceBarrier(1, &pToRT);

	// レンダーターゲットの設定
	D3D12_CPU_DESCRIPTOR_HANDLE handles[] = { target->get_rtv_handle() };
	list->OMSetRenderTargets(1, handles, false, nullptr);

	// レンダーターゲットのクリア
	list->ClearRenderTargetView(handles[0], back_ground_color, 0, nullptr);

	// リソースバリアでレンダーターゲットを RenderTarget から Present へ変更
	auto rtToP = ResourceBarrierHelper::create_resource_barrier(target->get_render_target(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	list->ResourceBarrier(1, &rtToP);

	// コマンドリストをクローズ
	list->Close();

	// コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { list };
	queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
	
	//	シグナルを送って配列に保存
	frame_resources[current_frame_index]->set_frame_fence_value(fence_->signal(graphics_queue->get_command_queue()));

	// プレゼント
	swap_chain->get_swapchain()->Present(1, 0);

	/* -- 更新後処理 -- */
	end_update_renderer();

	auto end = std::chrono::high_resolution_clock::now();

	if (update_timer_flag) {
		DEBUG_LOG("end = ", std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()), "us");
	}
}

//@brief	=== 描画更新前関数 ===
//@details	描画機能を更新する際に先に処理する必要があるものを呼び出す関数
void DirectXRenderer::begin_update_renderer() {

	frame_count++;
}

//@brief	=== 描画更新後関数 ===
//@details	描画機能を更新した後に処理する必要があるものを呼び出す関数
void DirectXRenderer::end_update_renderer() {

	//	フレームリソースサイクルを進める
	current_frame_index = (current_frame_index + 1) % frame_resouse_size;
}

//@brief == = フレームリソース使用可能確認関数 == =
//@details	フレームリソースが使用可能な状態か確認する関数
void DirectXRenderer::sync_frame_resource() {

	//	これから使うフレームリソースが使える状態か判断
	auto value = frame_resources[current_frame_index]->get_frame_fence_value();
	auto complete = fence_->get_completed_value();
	if (value > complete) {

		fence_->wait_to_completed_value(value);

		//DEBUG_LOG("DirectXRenderer :: wait() : frame = " ,std::to_string(current_frame_index),
		//	", value = ", std::to_string(value),", complete = ", std::to_string(complete));
	}
}

///====================================================================
/// 終了時処理関数
///====================================================================

//@brief	=== 描画機能終了処理関数 ===
//@details	描画機能破棄前最終処理(非同期処理の待機など)をするための関数
void DirectXRenderer::end_renderer() {

	//	すべてのフレームリソースが使われなくなるまで待機
	for (auto& value : frame_resources) {
		fence_->wait_to_completed_value(value->get_frame_fence_value());
	}

	DEBUG_LOG("DirectXRenderer :: end_renderer()");
	DEBUG_LOG("DirectXRenderer :: frame_count = ", frame_count);
}