#pragma once

/* ========== Includeファイル ========== */

#include"../Windows/Window.h"
#include"ApplicationDataShare.h"

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	/// <summary>
	/// アプリケーションクラス
	/// </summary>
	class Application final
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		Application();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Application();

		[[nodiscard]] bool start_app();

	private:
		/* ========== Privateメンバー変数 ========== */

		Windows::Window main_window{};

		ApplicationDataShare data_share{};

		/* ========== Privateメンバー関数 ========== */

		/* ===== 初期化関数 ===== */

		[[nodiscard]] bool initialize_app();

		[[nodiscard]] bool initialize_window(
			const Windows::WindowSize& size
		);

		/* ===== 実行関数 ===== */

		void run_app();

		/* ===== 終了時関数 ===== */
		void end_app();

	};
}