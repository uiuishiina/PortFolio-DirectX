
///====================================================================
/// IncludeFile 参照まとめ
///====================================================================

#include"DirectX/DirectXRendererContext.h"
#include"DirectX/DirectXInitializer.h"
#include"DirectX/DrawResouces.h"

/* -- 各Factory -- */
#include"DirectX/Factory&Builder&Helper/CommandObjectFactory.h"
#include"DirectX/Factory&Builder&Helper/FrameResourceFactory.h"

/* -- 各ヘルパー -- */
#include"DirectX/Factory&Builder&Helper/PipelineStateHelper.h"

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

	//@brief	== フレームリソースインデックス確認フラグ ==
	const bool frame_index_flag = false;

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
	
	/* ==================== 作成開始 ==================== */

	renderer_context = std::make_unique<DirectXRendererContext>();

	//	描画機能初期化
	if (!DirectXInitializer::initialze_graphics(renderer_context.get(), buffer_size, frame_resouse_size, hwnd, window_size)) {
		return false;
	}

	//	描画機能リソース初期化
	if (!DirectXInitializer::initialize_graphics_resource(renderer_context.get())) {
		return false;
	}

	//	GPUリソース初期化
	if (!DirectXInitializer::initialize_GPU_resource(renderer_context.get())) {
		return false;
	}

	//	描画パス初期化
	if (!DirectXInitializer::initialize_draw_pass(renderer_context.get())) {
		return false;
	}

	pass_order = { "Normal_pass","Color_pass" };

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
	const auto backBufferIndex = renderer_context->swap_chain->get_swapchain()->GetCurrentBackBufferIndex();

	auto allocator = renderer_context->frame_resources[current_frame_index]->get_graphics_allocator();

	// コマンドアロケータリセット
	allocator->reset_command_allocator();
	// コマンドリストリセット
	renderer_context->graphics_list->reset_command_list(allocator->get_command_allocator());

	//	描画リソースセット
	resources::DrawResources resources{};
	resources.graphics_list = renderer_context->graphics_list->get_graphics_command_list();
	resources.frame_resource = renderer_context->frame_resources[current_frame_index].get();
	resources.static_heap_container = renderer_context->static_heap_container.get();
	resources.render_targets[resources::to_index(RenderTargetSlot::BackBuffer)] = renderer_context->back_buffers[backBufferIndex].get();
	resources.depth_targets[resources::to_index(DepthSlot::MainDepth)] = renderer_context->frame_resources[current_frame_index]->get_deprh_buffer();

	resources.mesh_[0] = renderer_context->polygon_.get();
	resources.mesh_[1] = renderer_context->Color_polygon_.get();

	/* ==================== 描画パス実行 ==================== */

	for (auto& name : pass_order) {
		renderer_context->static_draw_pass_container->apply_draw_pass(name, resources);
	}

	/* ==================== 描画パス終了 ==================== */

	// コマンドリストをクローズ
	renderer_context->graphics_list->get_graphics_command_list()->Close();

	// コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { renderer_context->graphics_list->get_graphics_command_list()};
	renderer_context->graphics_queue->get_command_queue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
	
	//	シグナルを送って配列に保存
	renderer_context->frame_resources[current_frame_index]->set_frame_fence_value(renderer_context->fence_->signal(renderer_context->graphics_queue->get_command_queue()));

	auto t0 = std::chrono::high_resolution_clock::now();

	// プレゼント
	renderer_context->swap_chain->get_swapchain()->Present(1, 0);

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
	auto value = renderer_context->frame_resources[current_frame_index]->get_frame_fence_value();
	auto complete = renderer_context->fence_->get_completed_value();
	if (value > complete) {

		//	使えるまで待機
		renderer_context->fence_->wait_to_completed_value(value);

		if (frame_index_flag) {
			DEBUG_LOG("DirectXRenderer :: wait() : frame = ", std::to_string(current_frame_index),
				", value = ", std::to_string(value), ", complete = ", std::to_string(complete));
		}	
	}
}

///====================================================================
/// 終了時処理関数
///====================================================================

//@brief	=== 描画機能終了処理関数 ===
//@details	描画機能破棄前最終処理(非同期処理の待機など)をするための関数
void DirectXRenderer::end_renderer() {

	//	すべてのフレームリソースが使われなくなるまで待機
	for (auto& value : renderer_context->frame_resources) {
		renderer_context->fence_->wait_to_completed_value(value->get_frame_fence_value());
	}

	DEBUG_LOG("DirectXRenderer :: end_renderer()");
	DEBUG_LOG("DirectXRenderer :: frame_count = ", frame_count);
}

