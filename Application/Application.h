#pragma once

/* ========== Includeファイル ========== */

#include"System/System.h"
#include"System/LoopManager.h"

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

		SystemManager system_{};

		LoopManager loop_{ &system_ };

		/* ========== Privateメンバー関数 ========== */

		/* ===== 初期化関数 ===== */

		/// <summary>
		/// アプリケーション初期化関数
		/// </summary>
		/// <returns>初期化の成否</returns>
		[[nodiscard]] bool initialize_app();

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