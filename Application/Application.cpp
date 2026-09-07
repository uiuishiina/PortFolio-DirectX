#include"Application.h"
#include"../windowInterface/windowInterface.h"
#include"../RendererInterface/RendererInterface.h"
#include"../Application/Input/InputStateManager.h"
#include"SharedData/ApplicationSharedData.h"

#include"../windowInterface/windowFactory.h"
#include"../RendererInterface/RendererFactory.h"

#include"../Debug/DebugLogSystem.h"

/* ==================================================================== */
// クラス設定
/* ==================================================================== */

/// <summary>
/// コンストラクタ
/// </summary>
Application::Application() {
	DEBUG_LOG("Application() call");
}

/// <summary>
/// デストラクタ
/// </summary>
Application::~Application() {
	DEBUG_LOG("~Application() call");
}

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// アプリケーション初期化関数
/// </summary>
/// <returns>初期化の成否</returns>
[[nodiscard]] bool Application::initialize_App() {
	
	//	入力機能作成
	input_manager_ins = std::make_unique<input::InputStateManager>();

	//	連携お試し
	share_datas_ins = std::make_unique<sharedData::ApplicationSharedData>(input_manager_ins.get());
	share_datas_ins->add_share_data<bool>();

	//	メインウィンドウ作成
	if (!initialize_window()) {
		is_initialize_error = true;
		DEBUG_ERROR_LOG(" Application :: initialize_window() FAILED");
		return false;
	}

	//	描画機能作成
	if (!initialize_renderer()) {
		is_initialize_error = true;
		DEBUG_ERROR_LOG(" Application :: initialize_renderer() FAILED");
		return false;
	}

	DEBUG_LOG("Application :: initialize_App() SUCCESS");
	return true;
}

/// <summary>
/// アプリケーション動作関数
/// </summary>
/// <details>
/// 初期化失敗ならすぐ [ return ]
/// </details>
void Application::run_App() {

	//初期化失敗時
	if (is_initialize_error) {
		return;
	}

	//アプリケーションループ
	while (true) {

		//	入力更新
		input_manager_ins->update_frame();

		//	入力など取得
		main_window_ins->poll_events();

		//	ウィンドウが終了要求を受け取ったなら
		if (main_window_ins->should_close_window()) {
			break;
		}

		//	ウィンドウアクティブ分岐処理
		if (!main_window_ins->is_active_window()) {

			//	アクティブではなくなったなら
			if (is_active_app) {
				is_active_app = false;
				DEBUG_LOG("Application :: NotActive window");
			}
			continue;
		}
		else {

			//	アクティブになったなら
			if (!is_active_app) {
				is_active_app = true;
				DEBUG_LOG("Application :: Active window");
			}
		}

		//	ESCキーが押されたなら、ウィンドウ終了
		if (input_manager_ins->is_down(input::InputKeyBoard::Esc)) {
			main_window_ins->close_window();
			continue;
		}

		//	描画更新
		main_renderer_ins->update_renderer();
	}

	//	終了時処理
	end_App();
}

/* ==================================================================== */
// Privateメンバー関数
/* ==================================================================== */

/// <summary>
/// ウィンドウインスタンス初期化関数
/// </summary>
/// <returns>初期化の成否</returns>
[[nodiscard]] bool Application::initialize_window() {

	//	適当にサイズを用意
	auto A_window = WindowSize(1280, 720);
	auto B_window = WindowSize(1920, 1080);
	auto C_window = WindowSize(700, 700);
	auto D_window = WindowSize(100, 100);

	main_window_ins = window::windowFactory::create_window(A_window,input_manager_ins.get());
	return main_window_ins != nullptr;
}

/// <summary>
/// 描画機能インスタンス初期化関数
/// </summary>
/// <returns>初期化の成否</returns>
[[nodiscard]] bool Application::initialize_renderer() {

	main_renderer_ins = render::RendererFactory::create_renderer(main_window_ins.get(), share_datas_ins.get());
	return main_renderer_ins != nullptr;
}

/// <summary>
/// アプリケーション終了時処理関数
/// </summary>
/// <details>
/// [ run_App() ] 終了時に呼び出す
/// </details>
void Application::end_App() {

	//	描画機能終了処理
	main_renderer_ins->end_renderer();

	//	OS側が終了していないなら待機
	if (!main_window_ins->is_complete_destroy_window()) {
		do {
			main_window_ins->poll_events();
		} while (!main_window_ins->is_complete_destroy_window());
	}
}