#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include<cstdint>
#include<memory>

/// <summary>
/// Windows名前空間
/// </summary>
namespace Windows {

	/// <summary>
	/// ウィンドウサイズ構造体
	/// </summary>
	struct WindowSize {

		/* ========== メンバー変数 ========== */

		/// <summary>
		/// 横幅
		/// </summary>
		std::uint32_t x_{};

		/// <summary>
		/// 縦幅
		/// </summary>
		std::uint32_t y_{};

		/* ========== メンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		WindowSize() = default;

		/// <summary>
		/// 幅指定コンストラクタ
		/// </summary>
		/// <param name="x">横幅</param>
		/// <param name="y">縦幅</param>
		WindowSize(
			std::uint32_t x,
			std::uint32_t y
		) :
			x_{ x },
			y_{ y } {}

		/* ===== 演算子オーバーロード ===== */

		/// <summary>
		/// [ () ] 演算子オーバーロード
		/// </summary>
		/// <returns>[ 横幅 ][ 縦幅 ] の構造化束縛</returns>
		[[nodiscard]] auto operator () () const {
			return std::make_pair(x_, y_);
		}
	};

	/// <summary>
	/// ウィンドウクラス
	/// </summary>
	class Window final : public HandyItems::others::NonCopyableBase
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		Window();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Window();

		/* ===== 初期化関数 ===== */

		[[nodiscard]] bool initialize_window(
			const WindowSize& size
		);

		/* ===== 実行関数 ===== */

	private:
		/* ========== Privateメンバー変数 ========== */

		WindowSize size_{};

		/* ========== Privateメンバー関数 ========== */


	};
}