#pragma once
#include<memory>

/* ========== 前方宣言 ========== */

namespace window {
	class windowInterface;
}
namespace render {
	class RendererInterface;
}
namespace input {
	class InputStateManager;
}
namespace sharedData {
	class ApplicationSharedData;
}

/// <summary>
/// アプリケーションクラス
/// </summary>
class Application final
{
public:
	/* ========== クラス設定 ========== */

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Application();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Application();


	/* ========== Publicメンバー関数 ========== */
	
	/// <summary>
	/// アプリケーション初期化関数
	/// </summary>
	/// <returns>初期化の成否</returns>
	[[nodiscard]] bool initialize_App();

	/// <summary>
	/// アプリケーション動作関数
	/// </summary>
	/// <details>
	/// 初期化失敗ならすぐ [ return ]
	/// </details>
	void run_App();

private:
	/* ========== Privateメンバー変数 ========== */

	/* === アプリケーションフラグ === */

	/// <summary>
	/// 初期化失敗時ストップフラグ
	/// </summary>
	/// <details>
	/// 初期化失敗時に [ true ]
	/// </details>
	bool is_initialize_error = false;

	/// <summary>
	/// アプリケーションアクティブフラグ
	/// </summary>
	/// <details>
	/// ウィンドウがアクティブなら [ true ]
	/// </details>
	bool is_active_app = true;

	/* -- 連携お試し変数 -- */
	bool right = true;
	bool left = true;

	/// <summary>
	/// アプリケーションウィンドウインスタンス
	/// </summary>
	/// <details>
	/// OSに対応するウィンドウ [ 現状Windowsのみ ]
	/// </details>
	std::unique_ptr<window::windowInterface> main_window_ins{};

	/// <summary>
	/// アプリケーション描画機能インスタンス
	/// </summary>
	/// <details>
	/// OSに対応する描画機能 [ 現状DirectXのみ ]
	/// </details>
	std::unique_ptr<render::RendererInterface> main_renderer_ins{};

	/// <summary>
	/// アプリケーション入力機能マネージャーインスタンス
	/// </summary>
	std::unique_ptr<input::InputStateManager> input_manager_ins{};

	std::unique_ptr<sharedData::ApplicationSharedData> share_datas_ins{};


	/* ========== Privateメンバー関数 ========== */

	/// <summary>
	/// ウィンドウインスタンス初期化関数
	/// </summary>
	/// <returns>初期化の成否</returns>
	[[nodiscard]] bool initialize_window();

	/// <summary>
	/// 描画機能インスタンス初期化関数
	/// </summary>
	/// <returns>初期化の成否</returns>
	[[nodiscard]] bool initialize_renderer();

	/// <summary>
	/// アプリケーション終了時処理関数
	/// </summary>
	/// <details>
	/// [ run_App() ] 終了時に呼び出す
	/// </details>
	void end_App();
};