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

		//@brief	=== ウィンドウ作成関数 ===
		//@param	window_size	ウィンドウサイズ
		//@return	ウィンドウインスタンス
		static  std::unique_ptr<windowInterface> create_window(WindowSize window_size);

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