#pragma once

/// <summary>
/// 入力名前空間
/// </summary>
namespace input {

	/* ==================================================================== */
	// ボタン入力列挙体
	/* ==================================================================== */

	/*
		入力フラグ識別用列挙体
	*/

	/// <summary>
	/// キーボード入力フラグ列挙体
	/// </summary>
	enum class InputKeyBoard {

		/* -- 数値 -- */

		Zero,
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Ate,
		Nine,

		/* -- アルファベット -- */
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		N,
		M,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		/* -- Funcキー -- */

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,

		/* -- その他 -- */

		Space,
		Enter,
		Esc,
		Shift,
		Contrl,
		Tab,

		/* -- 矢印キー -- */

		UpArrow,
		DownArrow,
		LeftArrow,
		RightArrow,

		/* -- 配列用意用Enum -- */

		Count
	};

	/// <summary>
	/// マウス入力フラグ列挙体
	/// </summary>
	enum class InputMouse {

		Left,
		Right,

		Count
	};
}