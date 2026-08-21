#include "windowInterface.h"

//@brief	=== 現在フレームキー状態取得関数 ===
[[nodiscard]] input::InputFrame windowInterface::get_input_frame()const noexcept {
	return current_frame_key;
}


//@brief	=== ウィンドウサイズ取得関数 ===
//@return	ウィンドウサイズ構造体
[[nodiscard]] WindowSize windowInterface::get_window_size()const noexcept {
	return window_size;
}

//@breif	=== ウィンドウ終了フラグ取得関数 ===
//@return	ウィンドウ終了フラグ
[[nodiscard]] bool windowInterface::should_close_window()const noexcept {
	return should_close;
}

//@brief	=== ウィンドウアクティブ状態取得関数 ===
//@return	ウィンドウ動作フラグ
[[nodiscard]] bool windowInterface::is_active_window()const noexcept {
	return is_active;
}

//@brief	=== ウィンドウ破棄状態取得関数 ===
//@return	ウィンドウ破棄完了フラグ
[[nodiscard]] bool windowInterface::is_complete_destroy_window()const noexcept {
	return complete_destroy;
}
