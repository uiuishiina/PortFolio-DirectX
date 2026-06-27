#include"windowFactory.h"
#include"WindowsWindow.h"
#include"../Debug/DebugLogSystem.h"

//@brief	=== ウィンドウ作成関数 ===
//@param	window_size	ウィンドウサイズ
//@return	ウィンドウインスタンス
std::unique_ptr<windowInterface> windowFactory::create_window(WindowSize window_size) {

	std::unique_ptr<windowInterface> window_{};

#if defined(_WIN32)
    DEBUG_LOG("windowFactory :: create_window() = WindowsWindow");
    window_ = std::make_unique<WindowsWindow>();
    if (window_->create_window(window_size)) {
        return window_;
    }
#elif defined(__APPLE__)

#elif defined(__linux__)

#else

#endif
    return nullptr;
}