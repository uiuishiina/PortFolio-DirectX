#pragma once
#include"windowInterface.h"

///====================================================================
///	Windows.h 用前方宣言
///====================================================================

//HINSTANCE用前方宣言
struct HINSTANCE__;
using HINSTANCE = HINSTANCE__*;

//HWND用前方宣言
struct HWND__;
using HWND = HWND__*;

///====================================================================
/// WindowsWindow 派生クラス
///====================================================================

//@brief	=== Windowsウィンドウクラス ===
class WindowsWindow :public windowInterface
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	WindowsWindow() = default;
	~WindowsWindow() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	/* -- 継承関数 -- */

	//@breif	=== ウィンドウ作成関数 ===
	//@param	window_size	ウィンドウサイズ
	//@return	作成の可否
	[[nodiscard]] bool create_window(WindowSize size)override;

	//@breif	=== ウィンドウ破棄時処理関数 ===
	void on_destroy_window()override;

	//@breif	=== ウィンドウ破棄フラグ取得関数 ===
	//@return	ウィンドウ破棄フラグ
	bool should_close_window()const override;

	//@brief	=== OSイベント取得関数 ===
	void poll_events()override;

	//@brief	=== ウィンドウサイズ設定関数 ===
	//@param	new_size	ウィンドウサイズ
	void set_window_size(WindowSize new_size)override;

	//@brief	=== ウィンドウサイズ取得関数 ===
	//@return	ウィンドウサイズ構造体
	WindowSize get_window_size()const override;

	//@brief	=== ウィンドウハンドル取得関数 ===
	//@return	ウィンドウハンドルポインター
	void* get_native_handle()const override;

	//@brief	=== ウィンドウプロシージャ互換関数 ===
	//@param	msg	ウィンドウメッセージ互換
	//@param	wParam	wParam互換
	//@param	lParam	lParam互換
	void process_message(unsigned int msg, uintptr_t wParam, intptr_t lParam);

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== ウィンドウ終了フラグ ==
	bool is_stop = false;

	WindowSize window_size{};

	HINSTANCE hinstance_{};
	HWND hwnd_{};

	///====================================================================
	/// Private メンバー関数
	///====================================================================

	/* -- 独自関数 -- */

	//@brief	=== ウィンドウリサイズ時関数 ===
	//@param	new_size	ウィンドウサイズ
	void on_resize_window(WindowSize new_size);
};