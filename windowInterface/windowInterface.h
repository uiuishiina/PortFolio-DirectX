#pragma once

///====================================================================
/// WindowSize構造体
///====================================================================

//@brief	=== ウィンドウサイズ送受信用構造体 ===
struct WindowSize {

	int width{};
	int height{};

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

///====================================================================
/// windowInterface 基底クラス
///====================================================================

//@brief	=== ウィンドウインターフェースクラス ===
class windowInterface
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	windowInterface() = default;
	virtual ~windowInterface() = default;
	//コピー禁止,ムーブ禁止
	windowInterface(const windowInterface&) = delete;
	windowInterface& operator=(const windowInterface&) = delete;
	windowInterface(windowInterface&&) = delete;
	windowInterface& operator=(windowInterface&&) = delete;

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