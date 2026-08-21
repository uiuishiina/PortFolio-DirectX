#pragma once
#include"NonMovable.h"
#include"WindowSize.h"
#include"../Application/Input/InputFrame.h"

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

	/* === 純粋仮想関数 === */

	//@breif	=== ウィンドウ作成関数 ===
	//@param	size	ウィンドウサイズ
	//@return	作成の可否
	virtual [[nodiscard]] bool create_window(WindowSize size) = 0; 

	//@brief	=== OSイベント取得関数 ===
	virtual void poll_events() = 0;

	//@brief	=== ウィンドウ終了処理関数 ===
	virtual void close_window() = 0;

	//@breif	=== ウィンドウ破棄時処理関数 ===
	virtual void on_destroy_window() = 0;
	
	//@brief	=== ウィンドウハンドル取得関数 ===
	//@return	ウィンドウハンドルポインター
	virtual void* get_native_handle()const = 0;

	//@brief	=== ウィンドウサイズ設定関数 ===
	//@param	new_size	ウィンドウサイズ
	virtual void set_window_size(WindowSize new_size) = 0;


	/* === 共通フラグ & 変数 取得関数 === */
	
	//@brief	=== 現在フレームキー状態取得関数 ===
	//@return	現在フレームキー状態
	[[nodiscard]] input::InputFrame get_input_frame()const noexcept;

	//@brief	=== ウィンドウサイズ取得関数 ===
	//@return	ウィンドウサイズ構造体
	[[nodiscard]] WindowSize get_window_size()const noexcept;

	//@breif	=== ウィンドウ終了フラグ取得関数 ===
	//@return	ウィンドウ終了フラグ
	[[nodiscard]] bool should_close_window()const noexcept;

	//@brief	=== ウィンドウアクティブ状態取得関数 ===
	//@return	ウィンドウ動作フラグ
	[[nodiscard]] bool is_active_window()const noexcept;

	//@brief	=== ウィンドウ破棄状態取得関数 ===
	//@return	ウィンドウ破棄完了フラグ
	[[nodiscard]] bool is_complete_destroy_window()const noexcept;

protected:
	///====================================================================
	/// Protected メンバー変数
	///====================================================================

	//@brief	== ウィンドウ終了フラグ ==
	//@details	アプリケーション終了指令が来たなら [ true ]
	bool should_close = false;

	//@brief	== ウィンドウ動作フラグ ==
	//@details	フォーカスが合っていない(裏で動いている)なら [ false ]
	bool is_active = true;

	//@brief	== ウィンドウ破棄完了フラグ ==
	//@details	ウィンドウの破棄が完全に完了したなら [ true ]
	bool complete_destroy = false;

	//@brief	== ウィンドウサイズ保存変数 ==
	WindowSize window_size{};

	//@brief	== 現在フレームキー状態保存変数 ==
	//@param	poll_events()関数でキー更新をする設計
	input::InputFrame current_frame_key{};

};