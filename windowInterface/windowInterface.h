#pragma once
#include"NonMovable.h"
#include"WindowSize.h"

///====================================================================
/// windowInterface 基底クラス
///====================================================================

//@brief	=== ウィンドウインターフェースクラス ===
class windowInterface : public NonMovableBase
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	windowInterface() = default;
	virtual ~windowInterface() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@breif	=== ウィンドウ作成関数 ===
	//@param	size	ウィンドウサイズ
	//@return	作成の可否
	virtual [[nodiscard]] bool create_window(WindowSize size) = 0; 

	//@breif	=== ウィンドウ破棄時処理関数 ===
	virtual void on_destroy_window() = 0;

	//@breif	=== ウィンドウ破棄フラグ取得関数 ===
	//@return	ウィンドウ破棄フラグ
	virtual bool should_close_window()const = 0;

	//@brief	=== OSイベント取得関数 ===
	virtual void poll_events() = 0;

	//@brief	=== ウィンドウサイズ設定関数 ===
	//@param	new_size	ウィンドウサイズ
	virtual void set_window_size(WindowSize new_size) = 0;

	//@brief	=== ウィンドウサイズ取得関数 ===
	//@return	ウィンドウサイズ構造体
	virtual WindowSize get_window_size()const = 0;

	//@brief	=== ウィンドウハンドル取得関数 ===
	//@return	ウィンドウハンドルポインター
	virtual void* get_native_handle()const = 0;
};