#pragma once
#include<cstdint>

/// <summary>
/// ウィンドウサイズ送受信用構造体
/// </summary>
struct WindowSize {

	/* ========== メンバー変数 ========== */

	/// <summary>
	/// ウィンドウの横幅
	/// </summary>
	std::uint32_t width{};

	/// <summary>
	/// ウィンドウの立幅
	/// </summary>
	std::uint32_t height{};


	/* ========== メンバー関数 ========== */

	/// <summary>
	/// ウィンドウサイズ比較演算子オーバーロード
	/// </summary>
	/// <details>
	/// ウィンドウサイズが等しいか
	/// </details>
	/// <param name="athor">比較するウィンドウサイズ</param>
	/// <returns>等しいなら [ true ]</returns>
	bool operator==(const WindowSize& athor) const {
		return width == athor.width && height == athor.height;
	}

	/// <summary>
	/// 最小化チェック関数
	/// </summary>
	/// <details>
	/// 縦横が０なら最小とする
	/// </details>
	/// <returns>最小なら [ ture ]</returns>
	bool is_minimized()const {
		return width <= 0 && height <= 0;
	}

	/// <summary>
	/// 領域サイズチェック関数
	/// </summary>
	/// <details>
	/// いずれも最小じゃないなら領域があるとする
	/// </details>
	/// <returns>領域があるなら [ true ]</returns>
	bool has_area() const {
		return !is_minimized();
	}
};