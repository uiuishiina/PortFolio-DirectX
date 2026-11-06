#pragma once

/* ========== Includeファイル ========== */

#include"../Windows/Window.h"
#include"ApplicationDataShare.h"
#include"../DirectX/DirectXRenderer.h"

#include<memory>

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	//	前方宣言
	class ApplicationClock;

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

		/// <summary>
		/// アプリケーション開始関数
		/// </summary>
		/// <returns>開始したなら [ true ]</returns>
		[[nodiscard]] bool start_app();

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// メインウィンドウ
		/// </summary>
		Windows::Window main_window{};

		/// <summary>
		/// データ共有
		/// </summary>
		ApplicationDataShare data_share{};

		/// <summary>
		/// メインウィンドウ描画機能
		/// </summary>
		DirectX::DirectXRenderer main_renderer{};

		/// <summary>
		/// フレームレート管理
		/// </summary>
		std::unique_ptr<ApplicationClock> clock_{};

		/* ========== Privateメンバー関数 ========== */

		/* ===== 初期化関数 ===== */

		/// <summary>
		/// アプリケーション初期化関数
		/// </summary>
		/// <returns>初期化の成否</returns>
		[[nodiscard]] bool initialize_app();

		/// <summary>
		/// ウィンドウ初期化関数
		/// </summary>
		/// <param name="size">ウィンドウサイズ</param>
		/// <returns>初期化の成否</returns>
		[[nodiscard]] bool initialize_window(
			const Windows::WindowSize& size
		);

		/// <summary>
		/// 描画機能初期化関数
		/// </summary>
		/// <returns>初期化の成否</returns>
		[[nodiscard]] bool initialize_renderer();

		/* ===== 実行関数 ===== */

		/// <summary>
		/// アプリケーション実行関数
		/// </summary>
		void run_app();

		/* ===== 終了時関数 ===== */

		/// <summary>
		/// アプリケーション終了処理関数
		/// </summary>
		void end_app();

	};
}