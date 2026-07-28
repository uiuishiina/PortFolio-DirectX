
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
#include"DirectX/DirectXobject/PipelineState.h"
#include"DirectX/DirectXobject/Mesh.h"

/* -- DirectXObjectを利用したまとめクラス -- */
#include"DirectX/FrameResource.h"
#include"DirectX/Container/StaticHeapContainer.h"
#include"DirectX/Container/StaticShaderContainer.h"
#include"DirectX/Container/StaticRootSignatureContainer.h"
#include"DirectX/Container/StaticPiplineStateContainer.h"
#include"DirectX/Container/StaticDrawStateContainer.h"
#include"DirectX/Container/StaticRenderTargetStateContainer.h"

#include"DirectX/DrawResouces.h"
#include"DirectX/DrawPass/DrawPass.h"

/* -- 各Factory -- */
#include"DirectX/Factory&Builder&Helper/CommandObjectFactory.h"
#include"DirectX/Factory&Builder&Helper/FrameResourceFactory.h"

/* -- 各ヘルパー -- */
#include"DirectX/Factory&Builder&Helper/PiplineStateHelper.h"

#include"DirectX/Factory&Builder&Helper/RootSignatureDescBuilder.h"

/* -- その他 -- */
#include<chrono>
#include"DirectXRenderer.h"

#include"../Debug/DebugLogSystem.h"

///====================================================================
/// Using Name Space
///====================================================================

using namespace render::dx12;

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

	//	コンテナ各種インスタンス生成
	{
		static_heap_container = std::make_unique<container::StaticHeapContainer>();
		shader_container = std::make_unique<container::StaticShaderContainer>();
		root_signature_container = std::make_unique<container::StaticRootSignatureContainer>();
		pipline_container = std::make_unique<container::StaticPiplineStateContainer>();
		static_draw_state_container = std::make_unique<container::StaticDrawStateContainer>();
		static_render_target_state_container = std::make_unique<container::StaticRenderTargetStateContainer>();
	}

	//	DXGIインスタンス生成
	dxgi_ = std::make_unique<object::DXGI>();
	if (FAILED(dxgi_->initialize_DXGI())) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//	Deviceインスタンス生成
	device_ = std::make_unique<object::Device>();
	if (FAILED(device_->initialize_Device(dxgi_->get_DXGI_adaptor()))) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//	描画用コマンドキューインスタンス生成
	graphics_queue = std::make_unique<object::CommandQueue>();
	if (FAILED(factory::CommandObjectFactory::create_graphics_command_queue(device_->get_device(),*graphics_queue))) {
		DEBUG_LOG("DirectXRenderer :: create_command_queue() FAILED");
		return false;
	}

	//	フレームリソース生成
	if (FAILED(factory::FrameResourceFactory::create_frame_resources(device_->get_device(), frame_resouse_size, frame_resources))) {
		DEBUG_LOG("DirectXRenderer :: create_frame_resources() FAILED");
		return false;
	}

	//	描画用コマンドリストインスタンス生成
	graphics_list = std::make_unique<object::GraphicsCommandList>();
	if (FAILED(factory::CommandObjectFactory::create_graphics_command_list(device_->get_device(),
		frame_resources[0]->get_graphics_allocator()->get_command_allocator(), *graphics_list))) {
		DEBUG_LOG("DirectXRenderer :: create_command_queue() FAILED");
		return false;
	}
	
	//	初期作成ディスクリプタヒープコンテナインスタンス生成
	if (FAILED(static_heap_container->create_static_heap_container(device_->get_device(),
		{
			{D3D12_DESCRIPTOR_HEAP_TYPE_RTV,buffer_size,D3D12_DESCRIPTOR_HEAP_FLAG_NONE},//RTV
		}
	))) {
		DEBUG_LOG("DirectXRenderer :: create_static_heap_container() FAILED");
		return false;
	}

	//	スワップチェーンインスタンス生成
	swap_chain = std::make_unique<object::SwapChain>();
	if (FAILED(swap_chain->create_swapchain(dxgi_->get_DXGI_factory(), graphics_queue->get_command_queue(),
		window_size, hwnd, buffer_size))) {
		DEBUG_LOG("DirectXRenderer :: create_swapchain() FAILED");
		return false;
	}

	//	最終描画先レンダーターゲットインスタンス生成
	render_targets.resize(buffer_size);
	for (unsigned int i = 0; i < buffer_size; i++) {

		auto& p = render_targets[i];
		p = std::make_unique<object::RenderTarget>();
		if (FAILED(p->create_render_target(device_->get_device(), swap_chain->get_swapchain(),
			static_heap_container->get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)->get_cpu_descriptor_handle(i), i))) {
			DEBUG_LOG("DirectXRenderer :: create_swapchain() FAILED");
			return false;
		}
	}

	//	Fenceインスタンス生成
	fence_ = std::make_unique<object::Fence>();
	if (FAILED(fence_->create_fence(device_->get_device()))) {
		DEBUG_LOG("DirectXRenderer :: create_fence() FAILED");
		return false;
	}

	//	RootSignatureインスタンス生成
	desc::RootSignatureDesc root_desc{};
	builder::RootSignatureDescBuilder::add_flags(root_desc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	if (FAILED(root_signature_container->create_root_signature("Normal_root",device_->get_device(), root_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_root_signature() FAILED");
		return false;
	}

	//	シェーダーコンテナインスタンス生成&登録
	if (FAILED(shader_container->compile_shader("Normal_vs", L"../RendererInterface/HLSLshader/NormalVertexShader.hlsl", "main", "vs_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Normal_vs");
		return false;
	}
	const auto vs_hash = shader_container->get_hash_key("Normal_vs");

	if (FAILED(shader_container->compile_shader("Normal_ps", L"../RendererInterface/HLSLshader/NormalPixelShader.hlsl", "main", "ps_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Normal_ps");
		return false;
	}

	if (FAILED(shader_container->compile_shader("Color_vs", L"../RendererInterface/HLSLshader/ColorVertexShader.hlsl", "main", "vs_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Color_vs");
		return false;
	}
	if (FAILED(shader_container->compile_shader("Color_ps", L"../RendererInterface/HLSLshader/ColorPixelShader.hlsl", "main", "ps_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Color_ps");
		return false;
	}


	/* ==================== PiplineState作成 ==================== */

	desc::PipelineStateDesc pipline_desc{};

	//	頂点入力設定
	pipline_desc.input_elements = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//	必要なインスタンス設定
	pipline_desc.root_signature = root_signature_container->get_root_signature("Normal_root");
	pipline_desc.vs_hlsl = shader_container->get_shader("Normal_vs");
	pipline_desc.ps_hlsl = shader_container->get_shader("Normal_ps");

	pipline_desc.rasterizer_desc.FillMode = static_cast<D3D12_FILL_MODE>(3);	//	D3D12_FILL_MODE_WIREFRAME = 2,D3D12_FILL_MODE_SOLID = 3
	pipline_desc.blend_desc = helper::PiplineStateHepler::get_enable_blend();
	pipline_desc.depth_stencil_desc.DepthEnable = FALSE;
	pipline_desc.depth_stencil_desc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;

	if (FAILED(pipline_container->create_pipline_state("Normal_pipline", device_->get_device(), pipline_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_piplinestate() FAILED");
		return false;
	}

	normal_pipline = pipline_container->get_hash_key("Normal_pipline").value();


	//	PiplineStateインスタンス生成
	desc::PipelineStateDesc color_pipline{};

	//	頂点入力設定
	color_pipline.input_elements = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//	必要なインスタンス設定
	color_pipline.root_signature = root_signature_container->get_root_signature("Normal_root");
	color_pipline.vs_hlsl = shader_container->get_shader("Color_vs");
	color_pipline.ps_hlsl = shader_container->get_shader("Color_ps");

	color_pipline.rasterizer_desc.FillMode = static_cast<D3D12_FILL_MODE>(3);	//	D3D12_FILL_MODE_WIREFRAME = 2,D3D12_FILL_MODE_SOLID = 3
	color_pipline.blend_desc = helper::PiplineStateHepler::get_enable_blend();
	color_pipline.depth_stencil_desc.DepthEnable = FALSE;
	color_pipline.depth_stencil_desc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;

	if (FAILED(pipline_container->create_pipline_state("Color_pipline", device_->get_device(), color_pipline))) {
		DEBUG_LOG("DirectXRenderer :: create_piplinestate() FAILED");
		return false;
	}
	
	/* ==================== Mesh作成 ==================== */

	//	ポリゴンインスタンス生成
	polygon_ = std::make_unique<mesh::Mesh>();

	//	頂点情報作成

	struct normal_polygon {
		float pos_[3]{};
	};
	mesh::MeshDesc<normal_polygon> polygon_desc{};
	polygon_desc.vertex_data = {
		{-0.5f,-1.0f, 0.0f},
		{ 0.0f, 0.0f, 0.0f},
		{ 0.5f,-1.0f, 0.0f}
	};
	polygon_desc.index_data = {
		0,1,2
	};
	if (FAILED(polygon_->create_mesh(device_->get_device(), polygon_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_polygon() FAILED");
		return false;
	}

	//	ポリゴンインスタンス生成
	Color_polygon_ = std::make_unique<mesh::Mesh>();

	struct color_polygon {
		float pos_[3]{};
		float color_[4]{};
	};
	mesh::MeshDesc<color_polygon> color_mesh{};
	color_mesh.vertex_data = {
		{{ 0.5f, 1.0f, 0.0f},{ 1.0f, 0.0f, 0.0f, 1.0f}},//右
		{{ 0.0f, 0.0f, 0.0f},{ 0.0f, 1.0f, 0.0f, 1.0f}},//真ん中
		{{-0.5f, 1.0f, 0.0f},{ 0.0f, 0.0f, 1.0f, 1.0f}}	//左
	};
	color_mesh.index_data = {
		0,1,2
	};
	if (FAILED(Color_polygon_->create_mesh(device_->get_device(), color_mesh))) {
		DEBUG_LOG("DirectXRenderer :: create_polygon() FAILED");
		return false;
	}


	/* ==================== DrawPass作成 ==================== */

	/* -- NormalPass作成 -- */

	{
		NormalPass_ = std::make_unique<pass::DrawPass>();
		
		//	DrawState作成
		desc::DrawStateDesc draw_state_desc{};
		draw_state_desc.root_signature = root_signature_container->get_root_signature("Normal_root");
		draw_state_desc.pipline_state = pipline_container->get_pipline_state(normal_pipline);

		// ビューポート設定
		D3D12_VIEWPORT viewport{};
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(window_size.width);
		viewport.Height = static_cast<float>(window_size.height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		draw_state_desc.viewport_ = viewport;

		// シザー矩形設定
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;
		scissorRect.top = 0;
		scissorRect.right = window_size.width;
		scissorRect.bottom = window_size.height;
		draw_state_desc.rect_ = scissorRect;
		if (!static_draw_state_container->create_draw_state("Normal_State", draw_state_desc)) {
			DEBUG_LOG("DirectXRenderer :: creaate_draw_state() FAILED");
			return false;
		}

		//	DrawTargetState作成
		//	BackBufferを追加
		if (!static_render_target_state_container->create_render_target_state("NormalTarget", 
			{
						RenderTargetSlot::BackBuffer
			}
			)) {
			DEBUG_LOG("DirectXRenderer :: create_render_target_state() FAILED");
			return false;
		}

		//	DrawCommands作成
		NormalCommands_ = std::make_unique<command::DrawCommands>();
		NormalCommands_->set_begin_command(
			[&](resources::DrawResources& resource) {
				auto* target = resource.get_target(RenderTargetSlot::BackBuffer);
				target->barrier_transition(resource.graphics_list, D3D12_RESOURCE_STATE_RENDER_TARGET);
				resource.graphics_list->ClearRenderTargetView(target->get_rtv_handle(), back_ground_color, 0, nullptr);
			}
		);
		NormalCommands_->add_apply_command(
			[&](resources::DrawResources& resource) {
				polygon_->draw_mesh(graphics_list->get_graphics_command_list());
			}
		);

		NormalCommands_->set_end_command(
			[](resources::DrawResources& resource) {
				auto* target = resource.get_target(RenderTargetSlot::BackBuffer);
				target->barrier_transition(resource.graphics_list, D3D12_RESOURCE_STATE_PRESENT);

			}
		);

		if (!NormalPass_->initialize_pass(static_draw_state_container->get_draw_state("Normal_State"), static_render_target_state_container->get_draw_state("NormalTarget"), NormalCommands_.get())) {
			DEBUG_LOG("DirectXRenderer :: initialize_pass() FAILED");
			return false;
		}
	}

	/* -- ColorPass作成 -- */
	{

		Color_Pass_ = std::make_unique<pass::DrawPass>();

		//	DrawState作成
		desc::DrawStateDesc draw_state_desc{};
		draw_state_desc.root_signature = root_signature_container->get_root_signature("Normal_root");
		draw_state_desc.pipline_state = pipline_container->get_pipline_state("Color_pipline");

		// ビューポート設定
		D3D12_VIEWPORT viewport{};
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(window_size.width);
		viewport.Height = static_cast<float>(window_size.height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		draw_state_desc.viewport_ = viewport;

		// シザー矩形設定
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;
		scissorRect.top = 0;
		scissorRect.right = window_size.width;
		scissorRect.bottom = window_size.height;
		draw_state_desc.rect_ = scissorRect;
		if (!static_draw_state_container->create_draw_state("Color_State", draw_state_desc)) {
			DEBUG_LOG("DirectXRenderer :: creaate_draw_state() FAILED");
			return false;
		}

		//	DrawCommands作成
		Color_Commands_ = std::make_unique<command::DrawCommands>();
		Color_Commands_->set_begin_command(
			[&](resources::DrawResources& resource) {
				auto* target = resource.get_target(RenderTargetSlot::BackBuffer);
				target->barrier_transition(resource.graphics_list, D3D12_RESOURCE_STATE_RENDER_TARGET);
			}
		);
		Color_Commands_->add_apply_command(
			[&](resources::DrawResources& resource) {
				Color_polygon_->draw_mesh(graphics_list->get_graphics_command_list());
			}
		);

		Color_Commands_->set_end_command(
			[](resources::DrawResources& resource) {
				auto* target = resource.get_target(RenderTargetSlot::BackBuffer);
				target->barrier_transition(resource.graphics_list, D3D12_RESOURCE_STATE_PRESENT);
			}
		);

		if (!Color_Pass_->initialize_pass(static_draw_state_container->get_draw_state("Color_State"), static_render_target_state_container->get_draw_state("NormalTarget"), Color_Commands_.get())) {
			DEBUG_LOG("DirectXRenderer :: initialize_pass() FAILED");
			return false;
		}
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

/* ==================== 描画制御 ==================== */

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

	auto allocator = frame_resources[current_frame_index]->get_graphics_allocator();

	// コマンドアロケータリセット
	allocator->reset_command_allocator();
	// コマンドリストリセット
	graphics_list->reset_command_list(allocator->get_command_allocator());

	resources::DrawResources resources{};
	resources.graphics_list = graphics_list->get_graphics_command_list();
	resources.frame_resource = frame_resources[current_frame_index].get();
	resources.static_heap_container = static_heap_container.get();
	resources.render_targets[resources::to_index(RenderTargetSlot::BackBuffer)] = render_targets[backBufferIndex].get();

	/* ==================== 描画パス実行 ==================== */

	NormalPass_->apply(resources);
	Color_Pass_->apply(resources);

	/* ==================== 描画パス終了 ==================== */

	// コマンドリストをクローズ
	graphics_list->get_graphics_command_list()->Close();

	// コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { graphics_list->get_graphics_command_list()};
	graphics_queue->get_command_queue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
	
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

/* ==================== 描画前制御 ==================== */

//@brief	=== 描画更新前関数 ===
//@details	描画機能を更新する際に先に処理する必要があるものを呼び出す関数
void DirectXRenderer::begin_update_renderer() {

	frame_count++;
}

/* ==================== 描画後制御 ==================== */

//@brief	=== 描画更新後関数 ===
//@details	描画機能を更新した後に処理する必要があるものを呼び出す関数
void DirectXRenderer::end_update_renderer() {

	//	フレームリソースサイクルを進める
	current_frame_index = (current_frame_index + 1) % frame_resouse_size;
}

/* ==================== 描画待機制御 ==================== */

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

