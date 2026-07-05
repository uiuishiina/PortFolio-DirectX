
///====================================================================
/// IncludeFile 参照まとめ
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
#include"DirectX/DirectXobject/RootSignature.h"
#include"DirectX/DirectXobject/ShaderCompiler.h"
#include"DirectX/DirectXobject/PiplineState.h"
#include"DirectX/DirectXobject/Polygon.h"

/* -- DirectXObjectを利用したまとめクラス -- */
#include"DirectX/FrameResource.h"
#include"DirectX/StaticHeapContainer.h"
#include"DirectX/StaticShaderContainer.h"
#include"DirectX/StaticPiplineStateContainer.h"

/* -- 各Factory -- */
#include"DirectX/CommandObjectFactory.h"
#include"DirectX/FrameResourceFactory.h"

/* -- 各ヘルパー -- */
#include"DirectX/ResourceBarrierHelper.h"
#include"DirectX/PiplineStateHelper.h"

#include"DirectX/RootSignatureDescBuilder.h"

/* -- その他 -- */
#include<chrono>
#include"DirectXRenderer.h"

#include"../Debug/DebugLogSystem.h"

///====================================================================
/// 無名空間
///====================================================================

namespace {
	//@brief	== 初期化時タイマー計測フラグ ==
	const bool create_timer_flag = false;

	//@brief	== 描画ループ時タイマー計測フラグ ==
	const bool update_timer_flag = false;

	//@brief	=== タイマーデバッグ表示関数 ===
	//@param	name	出力ウィンドウに出す名前
	//@param	after	計測したい区間の後ろ
	//@param	before	計測したい区間の前
	static void debug_timer(const std::string& name, std::chrono::steady_clock::time_point& after, std::chrono::steady_clock::time_point& before) {
		DEBUG_LOG(name, std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(after - before).count()), "us");
	}
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

	/* ==================== 作成前処理 ==================== */

	auto start = std::chrono::high_resolution_clock::now();

	auto hwnd = (HWND)window->get_native_handle();
	window_size = window->get_window_size();
	
	frame_resources.resize(frame_resouse_size);

	/* ==================== 作成開始 ==================== */

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

	//	RootSignatureインスタンス生成
	root_ = std::make_unique<RootSignature>();
	RootSignatureDesc root_desc{};
	RootSignatureDescBuilder::add_flags(root_desc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	if (FAILED(root_->create_root_signature(device_->get_device(), root_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_root_signature() FAILED");
		return false;
	}

	//	シェーダーコンテナインスタンス生成&登録
	shader_container = std::make_unique<StaticShaderContainer>();
	if (FAILED(shader_container->compile_shader("Normal_vs", L"../RendererInterface/HLSLshader/NormalVertexShader.hlsl", "main", "vs_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Normal_vs");
		return false;
	}
	const auto vs_hash = shader_container->get_shader_hash_key("Normal_vs");

	if (FAILED(shader_container->compile_shader("Normal_ps", L"../RendererInterface/HLSLshader/NormalPixelShader.hlsl", "main", "ps_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Normal_ps");
		return false;
	}
	
	//	PiplineStateインスタンス生成
	pipline_container = std::make_unique<StaticPiplineStateContainer>();
	PipelineStateDesc pipline_desc{};

	//	頂点入力設定
	pipline_desc.input_elements = { 
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//	必要なインスタンス設定
	pipline_desc.root_signature = root_->get_root_signature();
	pipline_desc.vs_hlsl = shader_container->get_shader(vs_hash.value());
	pipline_desc.ps_hlsl = shader_container->get_shader("Normal_ps");

	pipline_desc.rasterizer_desc.FillMode = static_cast<D3D12_FILL_MODE>(3);	//	D3D12_FILL_MODE_WIREFRAME = 2,D3D12_FILL_MODE_SOLID = 3
	pipline_desc.blend_desc = PiplineStateHepler::get_enable_blend();
	
	if (FAILED(pipline_container->create_pipline_state("Normal_pipline", device_->get_device(), pipline_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_piplinestate() FAILED");
		return false;
	}

	normal_pipline = pipline_container->get_pipline_state_hash_key("Normal_pipline").value();

	//	ポリゴンインスタンス生成
	polygon_ = std::make_unique<polygon::Polygon>();

	//	頂点情報作成
	struct normal_polygon {
		float pos_[3]{};
		float color_[4]{};
	};
	polygon::PolygonDesc<normal_polygon> polygon_desc{};
	polygon_desc.vertex_data = {
		{{-0.5f,-0.5f, 0.0f},{ 1.0f, 0.0f, 0.0f, 1.0f}},
		{{ 0.0f, 0.5f, 0.0f},{ 0.0f, 1.0f, 0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.0f},{ 0.0f, 0.0f, 1.0f, 1.0f}}
	};
	polygon_desc.index_data = {
		0,1,2
	};
	if (FAILED(polygon_->create_polygon(device_->get_device(), polygon_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_polygon() FAILED");
		return false;
	}

	auto end = std::chrono::high_resolution_clock::now();

	if (create_timer_flag) {
		debug_timer("create = ", end, start);
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

	/* ==================== 更新前処理 ==================== */

	// 外部との連携
	begin_update_renderer();

	//	リソース待機
	sync_frame_resource();

	/* ==================== 描画機能更新 ==================== */

	/* - 準備 - */
	//	描画先のバッファインデックスを取得
	const auto backBufferIndex = swap_chain->get_swapchain()->GetCurrentBackBufferIndex();

	//	参照を保存
	auto* queue = graphics_queue->get_command_queue();
	auto* list = graphics_list->get_graphics_command_list();
	auto* allocator = frame_resources[current_frame_index]->get_graphics_allocator();
	auto target = render_targets[backBufferIndex].get();

	// コマンドアロケータリセット
	allocator->reset_command_allocator();
	// コマンドリストリセット
	graphics_list->reset_command_list(allocator->get_command_allocator());

	/* - 更新開始 - */
	// リソースバリアでレンダーターゲットを Present から RenderTarget へ変更
	auto pToRT = ResourceBarrierHelper::create_resource_barrier(target->get_render_target(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	list->ResourceBarrier(1, &pToRT);

	// レンダーターゲットの設定
	D3D12_CPU_DESCRIPTOR_HANDLE handles[] = { target->get_rtv_handle() };
	list->OMSetRenderTargets(1, handles, false, nullptr);

	// レンダーターゲットのクリア
	list->ClearRenderTargetView(handles[0], back_ground_color, 0, nullptr);


	// パイプラインステートとルートシグネチャの設定
	list->SetGraphicsRootSignature(root_->get_root_signature());
	list->SetPipelineState(pipline_container->get_pipline_state(normal_pipline));

	// ビューポート設定
	D3D12_VIEWPORT viewport{};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(window_size.width);
	viewport.Height = static_cast<float>(window_size.height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	list->RSSetViewports(1, &viewport);

	// シザー矩形設定
	D3D12_RECT scissorRect{};
	scissorRect.left = 0;
	scissorRect.top = 0;
	scissorRect.right = window_size.width;
	scissorRect.bottom = window_size.height;
	list->RSSetScissorRects(1, &scissorRect);

	// ポリゴンの描画
	polygon_->draw_polygon(list);

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

	auto t0 = std::chrono::high_resolution_clock::now();

	// プレゼント
	swap_chain->get_swapchain()->Present(1, 0);

	auto t1 = std::chrono::high_resolution_clock::now();
	if (update_timer_flag) {
		debug_timer("present = ", t1, t0);
	}

	/* ==================== 更新後処理 ==================== */

	//	次フレーム移行への後処理
	end_update_renderer();

	auto end = std::chrono::high_resolution_clock::now();
	if (update_timer_flag) {
		debug_timer("update = ", end, start);
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

		//	使えるまで待機
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