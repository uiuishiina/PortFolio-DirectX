#pragma once
#include"windowInterface.h"
#include<memory>

/// <summary>
/// ウィンドウ名前空間
/// </summary>
namespace window {

	/// <summary>
	/// ウィンドウファクトリークラス
	/// </summary>
	class windowFactory final
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// ウィンドウインスタンス作成関数
		/// </summary>
		/// <param name="window_size">設定するウィンドウサイズ構造体</param>
		/// <param name="input_">入力機能マネージャークラス参照</param>
		/// <returns>ウィンドウインスタンス</returns>
		static  std::unique_ptr<windowInterface> create_window(WindowSize window_size, input::InputStateManager* input_);

	private:
		/* ========== クラス設定 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		windowFactory() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~windowFactory() = default;

	};
}