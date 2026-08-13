#pragma once

///====================================================================
/// WindowSize構造体
///====================================================================

//@brief	=== ウィンドウサイズ送受信用構造体 ===
struct WindowSize {

	//@brief	== ウィンドウの横幅 ==
	int width{};

	//@brief	== ウィンドウの立幅 ==
	int height{};

	//@brief	=== ウィンドウサイズ比較演算子オーバーロード ===
	bool operator==(const WindowSize& athor) const {
		return width == athor.width && height == athor.height;
	}

	//@brief	=== 最小化チェック関数 ===
	//@return	最小なら [ ture ]
	bool is_minimized()const {
		return width <= 0 && height <= 0;
	}

	//@brief	=== 領域サイズチェック関数 ===
	//@return	領域があるなら []
	bool has_area() const {
		return width > 0 && height > 0;
	}
};