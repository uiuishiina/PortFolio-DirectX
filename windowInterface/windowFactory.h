#pragma once
#include"windowInterface.h"
#include<memory>

///====================================================================
/// windowFactory クラス
///====================================================================

//@brief	=== ウィンドウファクトリークラス ===
class windowFactory final
{
public:
	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== ウィンドウ作成関数 ===
	//@param	window_size	ウィンドウサイズ
	//@return	ウィンドウインスタンス
	static std::unique_ptr<windowInterface> create_window(WindowSize window_size);
};