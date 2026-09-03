
///====================================================================
/// IncludeFile 参照まとめ
///====================================================================

#include"DirectX/DirectXRendererContext.h"
#include"DirectX/DirectXInitializer.h"
#include"DirectX/DirectXUpdater.h"
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
[[nodiscard]] bool DirectXRenderer::create_renderer(window::windowInterface* window, sharedData::ApplicationSharedData* shared_datas) {

	/* ==================== 作成前処理 ==================== */

	auto start = std::chrono::high_resolution_clock::now();

	window_handle = window->get_native_handle();
	auto hwnd = std::any_cast<HWND>(window_handle);
	if (hwnd == nullptr) {
		DEBUG_ERROR_LOG("DirectXRenderer :: hwnd nullptr");
		return false;
	}

	window_size = window->get_window_size();

	app_shared_datas = shared_datas;
	
	/* ==================== 作成開始 ==================== */

	//DirectX描画機能インスタンス作成
		
	renderer_context = std::make_unique<DirectXRendererContext>();

	//	描画機能初期化
	if (!DirectXInitializer::initialze_graphics(renderer_context.get(), buffer_size, frame_resouse_size, *hwnd, window_size)) {
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

	pass_order = DirectXInitializer::get_draw_pass_order();


	//DirectX描画機能更新クラス作成

	renderer_updater = std::make_unique<DirectXUpdater>(renderer_context.get());


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

	//	更新前
	begin_update_renderer();
	
	//	非同期待機
	renderer_updater->sync_frame_resource();

	/* ==================== 描画機能 & リソース 更新 ==================== */

	//	更新前リセット
	renderer_updater->reset_frame_resource();

	/* ==================== 描画パス実行 ==================== */

	const auto value = app_shared_datas->get_share_data<bool>()->get_reference_to_index(0);
	const auto left = app_shared_datas->get_share_data<bool>()->get_reference_to_index(1);

	if (value.has_value() && left.has_value()) {

		if (value.value() && left.value()) {
			renderer_updater->apply_draw_pass(pass_order);
		}
		else if (value.value() && !left.value()) {
			std::vector<std::string> v = { "Clear_pass","Normal_pass" };
			renderer_updater->apply_draw_pass(v);
		}
		else if (!value.value() && left.value()) {
			std::vector<std::string> v = { "Clear_pass","Color_pass" };
			renderer_updater->apply_draw_pass(v);
		}
		else {
			std::vector<std::string> v = { "Clear_pass" };
			renderer_updater->apply_draw_pass(v);
		}

	}

	/* ==================== 描画パス終了 ==================== */

	//	描画コマンド実行
	renderer_updater->execute_command_lists();

	auto t0 = std::chrono::high_resolution_clock::now();

	//	バックバッファプレゼント
	renderer_updater->present();

	auto t1 = std::chrono::high_resolution_clock::now();
	if (update_timer_flag) {
		debug_timer("present = ", t1, t0);
	}

	/* ==================== 更新後処理 ==================== */

	//	更新後
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

	if (!renderer_updater->begin_update_renderer()) {

		//	ここにきているならエラー
		return;
	}
}



/* ==================== 描画後制御 ==================== */

//@brief	=== 描画更新後関数 ===
//@details	描画機能を更新した後に処理する必要があるものを呼び出す関数
void DirectXRenderer::end_update_renderer() {

	renderer_updater->end_update_renderer();
}

///====================================================================
/// 終了時処理関数
///====================================================================

//@brief	=== 描画機能終了処理関数 ===
//@details	描画機能破棄前最終処理(非同期処理の待機など)をするための関数
void DirectXRenderer::end_renderer() {

	renderer_updater->end_updater();

	DEBUG_LOG("DirectXRenderer :: end_renderer()");
}