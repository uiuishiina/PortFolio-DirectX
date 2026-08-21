#pragma once
#include<memory>

class windowInterface;
class RendererInterface;
namespace input {
	class InputStateManager;
}

///====================================================================
/// Application クラス
///====================================================================

//@brief	=== アプリケーションクラス ===
class Application final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	Application();
	~Application();

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== アプリケーション初期化関数 ===
	//@details	責務 [ 初期化指示 ] , [ アプリ詳細設定 ] 
	//@return	初期化の成否
	[[nodiscard]] bool initialize_App();

	//@brief	=== アプリケーション動作関数 ===
	//@details	責務 [ アプリケーションループ ] , [ 終了判断 ] 
	//@details	初期化失敗時すぐに [ return ] する
	void run_App();

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== アプリケーションストップフラグ ==
	//@details	初期化失敗時 [ ture ]
	bool is_initialize_error = false;

	//@brief	== アプリケーションウィンドウインスタンス ==
	//@details	対応するウィンドウ
	std::unique_ptr<windowInterface> main_window_ins{};

	//@brief	== アプリケーション描画機能インスタンス ==
	//@details	対応する描画機能
	std::unique_ptr<RendererInterface> main_renderer_ins{};

	//@breif	== アプリケーション入力機能マネージャーインスタンス ==
	std::unique_ptr<input::InputStateManager> input_manager_ins{};

	///====================================================================
	/// Private メンバー関数
	///====================================================================

	//@brief	=== ウィンドウインスタンス初期化関数 ===
	//@details	責務 [ ウィンドウインスタンス初期化 ] 
	[[nodiscard]] bool initialize_window();

	//@brief	=== 描画機能インスタンス初期化関数 ===
	//@details	責務 [ 描画機能インスタンス初期化 ]
	[[nodiscard]] bool initialize_renderer();

	//@brief	=== アプリケーション終了時処理関数 ===
	//@details	 [ run_App() ] の最後(アプリ終了時)に呼び出される
	void end_App();
};