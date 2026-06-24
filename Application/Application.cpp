
#include"../windowInterface/windowInterface.h"

#include"Application.h"

#include"../windowInterface/windowFactory.h"

///====================================================================

//コンストラクタ,デストラクタ
Application::Application() = default;
Application::~Application() = default;

///====================================================================
/// 初期化時関数
///====================================================================

//@brief	=== アプリケーション初期化関数 ===
//@return	初期化の成否
[[nodiscard]] bool Application::initialize_App() {

	if (!initialize_window()) {
		is_initialize_error = true;
		return false;
	}

	return true;
}

//@brief	=== ウィンドウインスタンス初期化関数 ===
//@details	責務 [ ウィンドウインスタンス初期化 ] 
[[nodiscard]] bool Application::initialize_window() {

	main_window_ins = windowFactory::create_window(WindowSize(1280, 720));
	return main_window_ins != nullptr;
}

///====================================================================
/// 実行時関数
///====================================================================

//@brief	=== アプリケーション動作関数 ===
//@details	責務 [ アプリケーションループ ] , [ 終了判断 ] 
//@details	初期化失敗時すぐに [ return ] する
void Application::run_App() {

	//初期化失敗時
	if (is_initialize_error) {
		return;
	}

	//アプリケーションループ
	while (!main_window_ins->should_close_window()) {

		main_window_ins->poll_events();
	}

	//終了時処理
	end_App();
}

///====================================================================
/// 終了時関数
///====================================================================

//@brief	=== アプリケーション終了時処理関数 ===
//@details	 [ run_App() ] の最後(アプリ終了時)に呼び出される
void Application::end_App() {

}