#include "DirectXInitializer.h"

#include"DrawResouces.h"

/* -- 各Factory -- */
#include"Factory&Builder&Helper/CommandObjectFactory.h"
#include"Factory&Builder&Helper/FrameResourceFactory.h"

/* -- 各ヘルパー -- */
#include"Factory&Builder&Helper/PipelineStateHelper.h"
#include"Factory&Builder&Helper/RootSignatureDescBuilder.h"
#include"Factory&Builder&Helper/ViewportHelper.h"
#include"Factory&Builder&Helper/ScissorRectHelper.h"

#include"DrawPass/DrawPass.h"
#include"DrawPass/CommandPass.h"

/* -- その他 -- */
#include<chrono>
#include"ReferenceQueue.h"
#include"../Debug/DebugLogSystem.h"

using namespace render::dx12;

///====================================================================
/// 無名空間
///====================================================================

namespace {

	//@brief	== 初期化時使用ウィンドウサイズ変数 ==
	//@details	グローバルな変数を活用してみたらというアドバイスを参考にお試し
	WindowSize window_size{};

	//@brief	== 初期化時使用背景色保存関数 ==
	const float back_ground_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//@breif	== 初期作成時描画パス実行順保存配列 ==
	//@details	初期作成時に [ DirectXRenderer ] 側に取得させたいがインスタンス化や引数参照で受け渡すのが面倒だったのでここで保存してみる
	std::vector<std::string> pass_order{};

};

///====================================================================
/// 初期化関数
///====================================================================

///====================================================================
/// 描画機能初期化
///====================================================================

//@brief	=== 描画機能初期化関数 ===
//@param	context		描画機能インスタンス保存クラス参照
//@param	back_buffe_size			バックバッファサイズ
//@param	frame_resource_size		フレームリソースサイズ
//@param	hwnd					描画先ウィンドウハンドル
//@param	window_size				描画先ウィンドウサイズ構造体
//@return	初期化の成否
[[nodiscard]] bool DirectXInitializer::initialze_graphics(DirectXRendererContext* context
	, UINT back_buffe_size, UINT frame_resource_size, HWND hwnd, WindowSize size) {

	window_size = size;

	//	DXGIインスタンス生成
	if (FAILED(context->dxgi_->initialize_DXGI())) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//	Deviceインスタンス生成
	if (FAILED(context->device_->initialize_Device(context->dxgi_->get_DXGI_adaptor()))) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//キャッシュ
	const auto deviceP = context->device_->get_device();

	//	描画用コマンドキューインスタンス生成
	if (FAILED(factory::CommandObjectFactory::create_graphics_command_queue(deviceP, *context->graphics_queue))) {
		DEBUG_LOG("DirectXRenderer :: create_command_queue() FAILED");
		return false;
	}

	//	描画先用ディスクリプタヒープ生成
	if (FAILED(context->static_heap_container->create_static_heap_container(deviceP,
		{
			{D3D12_DESCRIPTOR_HEAP_TYPE_RTV,back_buffe_size,D3D12_DESCRIPTOR_HEAP_FLAG_NONE},				//RTV
		}
		))) {
		DEBUG_LOG("DirectXRenderer :: create_static_heap_container() FAILED");
		return false;
	}

	//	スワップチェーンインスタンス生成
	if (FAILED(context->swap_chain->create_swapchain(context->dxgi_->get_DXGI_factory(), context->graphics_queue->get_command_queue(),
		window_size, hwnd, back_buffe_size))) {
		DEBUG_LOG("DirectXRenderer :: create_swapchain() FAILED");
		return false;
	}

	//	バックバッファ配列インスタンス生成
	context->back_buffers.resize(back_buffe_size);
	for (unsigned int i = 0; i < back_buffe_size; i++) {

		auto& p = context->back_buffers[i];
		p = std::make_unique<object::BackBuffer>();
		if (FAILED(p->create_back_buffer(deviceP, context->swap_chain->get_swapchain(),
			context->static_heap_container->get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)->get_cpu_descriptor_handle(i), i))) {
			DEBUG_LOG("DirectXRenderer :: create_back_buffer() FAILED");
			return false;
		}
	}

	//	フレームリソース生成
	if (FAILED(factory::FrameResourceFactory::create_frame_resources(context, window_size, frame_resource_size, {}))) {
		DEBUG_LOG("DirectXRenderer :: create_frame_resources() FAILED");
		return false;
	}

	//	描画用コマンドリストインスタンス生成
	if (FAILED(factory::CommandObjectFactory::create_graphics_command_list(deviceP,
		context->frame_resources[0]->get_graphics_allocator()->get_command_allocator(), *context->graphics_list))) {
		DEBUG_LOG("DirectXRenderer :: create_command_queue() FAILED");
		return false;
	}

	//	Fenceインスタンス生成
	if (FAILED(context->fence_->create_fence(deviceP))) {
		DEBUG_LOG("DirectXRenderer :: create_fence() FAILED");
		return false;
	}

	return true;
}



///====================================================================
/// 描画機能リソース初期化
///====================================================================

//@brief	=== 描画機能リソース初期化関数 ===
//@param	context		描画機能インスタンス保存クラス参照
//@return	初期化の成否
[[nodiscard]] bool DirectXInitializer::initialize_graphics_resource(DirectXRendererContext* context) {

	//	シェーダー初期化
	if (!compile_shader(context)) {
		return false;
	}

	//	描画パイプライン初期化
	if (!initialize_pipline(context)) {
		return false;
	}

	return true;
}


//@brief	=== シェーダー初期化関数 ===
//@param	context		描画機能インスタンス保存クラス参照
//@return	初期化の成否
[[nodiscard]] bool DirectXInitializer::compile_shader(DirectXRendererContext* context) {

	//	シェーダーコンテナインスタンス生成&登録
	if (FAILED(context->shader_container->compile_shader("Normal_vs", L"../RendererInterface/HLSLshader/NormalVertexShader.hlsl", "main", "vs_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Normal_vs");
		return false;
	}
	if (FAILED(context->shader_container->compile_shader("Normal_ps", L"../RendererInterface/HLSLshader/NormalPixelShader.hlsl", "main", "ps_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Normal_ps");
		return false;
	}

	if (FAILED(context->shader_container->compile_shader("Color_vs", L"../RendererInterface/HLSLshader/ColorVertexShader.hlsl", "main", "vs_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Color_vs");
		return false;
	}
	if (FAILED(context->shader_container->compile_shader("Color_ps", L"../RendererInterface/HLSLshader/ColorPixelShader.hlsl", "main", "ps_5_0"))) {
		DEBUG_LOG("DirectXRenderer :: compile_shader() FAILED : Color_ps");
		return false;
	}

	return true;
}

//@breif	=== 描画パイプライン初期化関数 ===
//@param	context		描画機能インスタンス保存クラス参照
//@return	初期化の成否
[[nodiscard]] bool DirectXInitializer::initialize_pipline(DirectXRendererContext* context) {

	//キャッシュ
	const auto deviceP = context->device_->get_device();

	/* ==================== RootSignature作成 ==================== */

	//	RootSignatureインスタンス生成
	desc::RootSignatureDesc root_desc{};
	builder::RootSignatureDescBuilder::add_flags(root_desc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	if (FAILED(context->root_signature_container->create_root_signature("Normal_root", deviceP, root_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_root_signature() FAILED");
		return false;
	}

	/* ==================== PiplineState作成 ==================== */

	//Normal

	desc::PipelineStateDesc pipline_desc{};

	//	頂点入力設定
	pipline_desc.input_elements = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//	必要なインスタンス設定
	pipline_desc.root_signature = context->root_signature_container->get_root_signature("Normal_root");
	pipline_desc.vs_hlsl = context->shader_container->get_shader("Normal_vs");
	pipline_desc.ps_hlsl = context->shader_container->get_shader("Normal_ps");

	pipline_desc.rasterizer_desc.FillMode = static_cast<D3D12_FILL_MODE>(3);	//	D3D12_FILL_MODE_WIREFRAME = 2,D3D12_FILL_MODE_SOLID = 3
	pipline_desc.blend_desc = helper::PipelineStateHelper::get_enable_blend();
	pipline_desc.depth_stencil_desc = helper::PipelineStateHelper::get_enable_depth();


	auto depth_format = context->frame_resources[0]->get_deprh_buffer()->get_resource()->GetDesc().Format;
	//フォーマット指定
	pipline_desc.dsv_format = depth_format;

	if (FAILED(context->pipline_container->create_pipline_state("Normal_pipline", deviceP, pipline_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_piplinestate() FAILED");
		return false;
	}

	//Color

	//	PiplineStateインスタンス生成
	desc::PipelineStateDesc color_pipline{};

	//	頂点入力設定
	color_pipline.input_elements = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//	必要なインスタンス設定
	color_pipline.root_signature = context->root_signature_container->get_root_signature("Normal_root");
	color_pipline.vs_hlsl = context->shader_container->get_shader("Color_vs");
	color_pipline.ps_hlsl = context->shader_container->get_shader("Color_ps");

	color_pipline.rasterizer_desc.FillMode = static_cast<D3D12_FILL_MODE>(3);	//	D3D12_FILL_MODE_WIREFRAME = 2,D3D12_FILL_MODE_SOLID = 3
	color_pipline.blend_desc = helper::PipelineStateHelper::get_enable_blend();
	color_pipline.depth_stencil_desc = helper::PipelineStateHelper::get_enable_depth();

	//フォーマット指定
	color_pipline.dsv_format = depth_format;

	if (FAILED(context->pipline_container->create_pipline_state("Color_pipline", deviceP, color_pipline))) {
		DEBUG_LOG("DirectXRenderer :: create_piplinestate() FAILED");
		return false;
	}

	return true;
}


///====================================================================
/// GPUリソース初期化
///====================================================================

//@breif	=== GPUリソース初期化関数 ===
//@param	context		描画機能インスタンス保存クラス参照
//@return	初期化の成否
[[nodiscard]] bool DirectXInitializer::initialize_GPU_resource(DirectXRendererContext* context) {

	//キャッシュ
	const auto deviceP = context->device_->get_device();

	//	StaticBufferResourceクラスで作成するDefaultリソース等を作成

	auto allocator = context->frame_resources[0]->get_graphics_allocator();

	allocator->reset_command_allocator();
	context->graphics_list->reset_command_list(allocator->get_command_allocator());

	//	Upload用リソース配列用意
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> upload_resources{};
	upload_resources.resize(4);

	//	参照をキューに追加
	ReferenceQueue<Microsoft::WRL::ComPtr<ID3D12Resource>> upload_queue{};
	upload_queue.push_queue(upload_resources);

	/* ==================== Mesh作成 ==================== */

	/* ==================== NormalPolygon作成 ==================== */

	//	ポリゴンインスタンス生成

	//	描画オブジェクトクラス作成
	auto Normal_Polygon = std::make_unique<drawobject::Mesh>();

	//	頂点情報作成

	struct normal_polygon {
		float pos_[3]{};
	};
	drawobject::MeshDesc<normal_polygon> polygon_desc{};
	polygon_desc.vertex_data = {
		{-0.5f,-1.0f, 0.5f},
		{ 0.0f, 1.0f, 0.5f},
		{ 0.5f,-1.0f, 0.5f}
	};
	polygon_desc.index_data = {
		0,1,2
	};

	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> normal_resource = { upload_queue.get_reference().value(),upload_queue.get_reference().value() };
	if (FAILED(Normal_Polygon->create_mesh(deviceP, context->graphics_list->get_graphics_command_list(), normal_resource, polygon_desc))) {
		DEBUG_LOG("DirectXRenderer :: create_polygon() FAILED");
		return false;
	}

	if (!context->static_draw_object_container->register_draw_object("NormalPolygon", std::move(Normal_Polygon))) {
		DEBUG_LOG("DirectXRenderer :: create_polygon() FAILED");
		return false;
	}

	/* ==================== ColorPolygon作成 ==================== */

	//	ポリゴンインスタンス生成

	//	描画オブジェクトクラス作成
	auto Color_Polygon = std::make_unique<drawobject::Mesh>();
	struct color_polygon {
		float pos_[3]{};
		float color_[4]{};
	};
	drawobject::MeshDesc<color_polygon> color_mesh{};
	color_mesh.vertex_data = {
		{{ 0.5f, 1.0f, 1.0f},{ 1.0f, 0.0f, 0.0f, 1.0f}},//右
		{{ 0.0f, 0.0f, 1.0f},{ 0.0f, 1.0f, 0.0f, 1.0f}},//真ん中
		{{-0.5f, 1.0f, 1.0f},{ 0.0f, 0.0f, 1.0f, 1.0f}}	//左
	};
	color_mesh.index_data = {
		0,1,2
	};

	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> color_resource = { upload_queue.get_reference().value(),upload_queue.get_reference().value() };
	if (FAILED(Color_Polygon->create_mesh(deviceP, context->graphics_list->get_graphics_command_list(), color_resource, color_mesh))) {
		DEBUG_LOG("DirectXRenderer :: create_polygon() FAILED");
		return false;
	}

	if (!context->static_draw_object_container->register_draw_object("ColorPolygon", std::move(Color_Polygon))) {
		DEBUG_LOG("DirectXRenderer :: create_polygon() FAILED");
		return false;
	}

	/* ==================== すべてまとめて作成 ==================== */

	//	リソース作成
	context->graphics_list->get_graphics_command_list()->Close();

	//	コマンドリスト送信
	ID3D12CommandList* ppCommandLists[] = { context->graphics_list->get_graphics_command_list() };
	context->graphics_queue->get_command_queue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//	フェンス設定
	const auto fence_value = context->fence_->signal(context->graphics_queue->get_command_queue());
	context->frame_resources[0]->set_frame_fence_value(fence_value);

	//	使えるまで待機
	context->fence_->wait_to_completed_value(fence_value);

	return true;
}



///====================================================================
/// 描画パス初期化
///====================================================================

//@brief	=== 描画パス初期化関数 ===
//@param	context		描画機能インスタンス保存クラス参照
//@return	初期化の成否
[[nodiscard]] bool DirectXInitializer::initialize_draw_pass(DirectXRendererContext* context) {

	//キャッシュ
	const auto deviceP = context->device_->get_device();

	///====================================================================
	/// CommandPass作成
	///====================================================================

	/* ==================== ClearPass作成 ==================== */

	{
		/* ==================== DrawCommands作成 ==================== */

		//	コマンド作成
		//	バックバッファバリアをTargetに変更
		if (!context->static_draw_commands_container->add_command_map("backbuffer_barrier_target",
			[](resources::DrawResources& resource) {

				auto* target = resource.get_render_target(RenderTargetSlot::BackBuffer);
				target->barrier_transition(resource.graphics_list, D3D12_RESOURCE_STATE_RENDER_TARGET);

			})) {
			DEBUG_LOG("DirectXRenderer :: add_command_map() FAILED");
		}

		//	バックバッファバリアをPresentに変更
		if (!context->static_draw_commands_container->add_command_map("backbuffer_barrier_present",
			[](resources::DrawResources& resource) {

				auto* target = resource.get_render_target(RenderTargetSlot::BackBuffer);
				target->barrier_transition(resource.graphics_list, D3D12_RESOURCE_STATE_PRESENT);

			})) {
			DEBUG_LOG("DirectXRenderer :: add_command_map() FAILED");
		}

		//	バックバッファとデプスバッファクリア
		if (!context->static_draw_commands_container->add_command_map("claer_backbuffer_and_depthbuffer",
			[](resources::DrawResources& resource) {

				auto* target = resource.get_render_target(RenderTargetSlot::BackBuffer);
				resource.graphics_list->ClearRenderTargetView(target->get_rtv_handle(), back_ground_color, 0, nullptr);

				auto* depth = resource.frame_resource->get_deprh_buffer();
				resource.graphics_list->ClearDepthStencilView(depth->get_dsv_handle(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

			})) {
			DEBUG_LOG("DirectXRenderer :: add_command_map() FAILED");
		}

		//	DrawCommands作成
		desc::DrawCommandDesc draw_commands_desc{};
		draw_commands_desc.begin_name = "backbuffer_barrier_target";
		draw_commands_desc.apply_names = { "claer_backbuffer_and_depthbuffer" };
		draw_commands_desc.end_name = "backbuffer_barrier_present";

		if (!context->static_draw_commands_container->create_draw_commands("Clear_Backbuffer", draw_commands_desc)) {
			DEBUG_LOG("DirectXRenderer :: create_draw_commands() FAILED");
			return false;
		}

		/* ==================== CommandPass作成 ==================== */

		auto clear_pass = std::make_unique<pass::CommandPass>();

		desc::CommandPassDesc clear_pass_desc(context->static_draw_commands_container->get_draw_commands("Clear_Backbuffer"));
		if (!clear_pass->initialize_pass(clear_pass_desc)) {
			DEBUG_LOG("DirectXRenderer :: initialize_pass() FAILED");
		}
		if (!context->static_draw_pass_container->register_draw_pass("Clear_pass", std::move(clear_pass))) {
			DEBUG_LOG("DirectXRenderer :: register_draw_pass() FAILED");
			return false;
		}
	}

	///====================================================================
	/// DrawPass作成
	///====================================================================

	/* ==================== NormalPass作成 ==================== */

	{
		/* ==================== DrawState作成 ==================== */

		desc::DrawStateDesc draw_state_desc{};
		draw_state_desc.root_signature = context->root_signature_container->get_root_signature("Normal_root");
		draw_state_desc.pipline_state = context->pipline_container->get_pipline_state("Normal_pipline");

		// ビューポート設定
		draw_state_desc.viewport_ = helper::ViewportHelper::create_viewport(static_cast<float>(window_size.width), static_cast<float>(window_size.height));

		// シザー矩形設定
		draw_state_desc.rect_ = helper::ScissorRectHelper::create_scissor_rect(window_size.width, window_size.height);

		if (!context->static_draw_state_container->create_draw_state("Normal_State", draw_state_desc)) {
			DEBUG_LOG("DirectXRenderer :: creaate_draw_state() FAILED");
			return false;
		}

		/* ==================== DrawRenderTargetState作成 ==================== */

		//	BackBufferとDepthBufferを描画先に指定
		if (!context->static_render_target_state_container->create_render_target_state("Normal_Target",
			{ RenderTargetSlot::BackBuffer },DepthSlot::MainDepth
		)) {
			DEBUG_LOG("DirectXRenderer :: create_render_target_state() FAILED");
			return false;
		}

		/* ==================== DrawCommands作成 ==================== */

		//	コマンド作成

		//	無色ポリゴン描画
		if (!context->static_draw_commands_container->add_command_map("draw_Normal_polygon",
			[](resources::DrawResources& resource) {

				resource.static_draw_object_container->get_draw_object("NormalPolygon")->draw(resource.graphics_list);

			})) {
			DEBUG_LOG("DirectXRenderer :: add_command_map() FAILED");
		}

		//	DrawCommands作成
		desc::DrawCommandDesc draw_commands_desc{};
		draw_commands_desc.begin_name = "backbuffer_barrier_target";
		draw_commands_desc.apply_names = { "draw_Normal_polygon" };
		draw_commands_desc.end_name = "backbuffer_barrier_present";

		if (!context->static_draw_commands_container->create_draw_commands("Normal_Commands", draw_commands_desc)) {
			DEBUG_LOG("DirectXRenderer :: create_draw_commands() FAILED");
			return false;
		}

		/* ==================== DrawPass作成 ==================== */

		desc::DrawPassDesc normal_pass_desc(
			context->static_draw_state_container->get_draw_state("Normal_State"),
			context->static_render_target_state_container->get_draw_state("Normal_Target"),
			context->static_draw_commands_container->get_draw_commands("Normal_Commands")
		);

		auto normal_pass = std::make_unique<pass::DrawPass>();
		if (!normal_pass->initialize_pass(normal_pass_desc)) {
			DEBUG_LOG("DirectXRenderer :: initialize_pass() FAILED");
		}
		if (!context->static_draw_pass_container->register_draw_pass("Normal_pass", std::move(normal_pass))) {
			DEBUG_LOG("DirectXRenderer :: register_draw_pass() FAILED");
			return false;
		}
	}

	/* ==================== ColorPass作成 ==================== */
	{
		/* ==================== DrawState作成 ==================== */
		desc::DrawStateDesc draw_state_desc{};
		draw_state_desc.root_signature = context->root_signature_container->get_root_signature("Normal_root");
		draw_state_desc.pipline_state = context->pipline_container->get_pipline_state("Color_pipline");

		// ビューポート設定
		draw_state_desc.viewport_ = helper::ViewportHelper::create_viewport(static_cast<float>(window_size.width), static_cast<float>(window_size.height));

		// シザー矩形設定
		draw_state_desc.rect_ = helper::ScissorRectHelper::create_scissor_rect(window_size.width, window_size.height);

		if (!context->static_draw_state_container->create_draw_state("Color_State", draw_state_desc)) {
			DEBUG_LOG("DirectXRenderer :: creaate_draw_state() FAILED");
			return false;
		}

		/* ==================== DrawCommands作成 ==================== */
		
		//	描画コマンド作成

		//	色付きポリゴン描画
		if (!context->static_draw_commands_container->add_command_map("draw_Color_polygon",
			[](resources::DrawResources& resource) {

				resource.static_draw_object_container->get_draw_object("ColorPolygon")->draw(resource.graphics_list);

			})) {
			DEBUG_LOG("DirectXRenderer :: add_command_map() FAILED");
		}

		//	DrawCommands作成
		desc::DrawCommandDesc draw_commands_desc{};
		draw_commands_desc.begin_name = "backbuffer_barrier_target";
		draw_commands_desc.apply_names = { "draw_Color_polygon" };
		draw_commands_desc.end_name = "backbuffer_barrier_present";

		if (!context->static_draw_commands_container->create_draw_commands("Color_Commands", draw_commands_desc)) {
			DEBUG_LOG("DirectXRenderer :: create_draw_commands() FAILED");
			return false;
		}

		/* ==================== DrawPass作成 ==================== */

		desc::DrawPassDesc color_pass_desc(
			context->static_draw_state_container->get_draw_state("Color_State"),
			context->static_render_target_state_container->get_draw_state("Normal_Target"),
			context->static_draw_commands_container->get_draw_commands("Color_Commands")
		);

		auto color_pass = std::make_unique<pass::DrawPass>();
		if (!color_pass->initialize_pass(color_pass_desc)) {
			DEBUG_LOG("DirectXRenderer :: initialize_pass() FAILED");
		}
		if (!context->static_draw_pass_container->register_draw_pass("Color_pass", std::move(color_pass))) {
			DEBUG_LOG("DirectXRenderer :: register_draw_pass() FAILED");
			return false;
		}
	}

	pass_order = { "Clear_pass","Normal_pass","Color_pass" };
	
	return true;
}


//@brief	=== 描画パス順取得関数 ===
//@details	内部でグローバル変数で保持(この先設計変更になる可能性あり)
//@return	初期化時に作った描画パス順配列
[[nodiscard]] std::vector<std::string> DirectXInitializer::get_draw_pass_order() noexcept {
	return pass_order;
}


///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 描画リソース作成関数 ===
//@details	描画に利用するリソースをフレームごとにまとめて構造体にする関数
//@return	描画リソース構造体
[[nodiscard]] resources::DrawResources DirectXInitializer::create_draw_resources(DirectXRendererContext* context, UINT64 current_frame_index) {

	//	描画先のバッファインデックスを取得
	const auto backBufferIndex = context->swap_chain->get_swapchain()->GetCurrentBackBufferIndex();

	//	描画リソースセット
	resources::DrawResources resources{};
	resources.graphics_list = context->graphics_list->get_graphics_command_list();
	resources.frame_resource = context->frame_resources[current_frame_index].get();
	resources.static_heap_container = context->static_heap_container.get();
	resources.static_draw_object_container = context->static_draw_object_container.get();

	resources.render_targets[to_index(RenderTargetSlot::BackBuffer)] = context->back_buffers[backBufferIndex].get();

	return resources;

}