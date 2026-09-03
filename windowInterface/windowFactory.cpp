#include"windowFactory.h"
#include"WindowsWindow.h"
#include"../Debug/DebugLogSystem.h"

using namespace window;

/// <summary>
/// ウィンドウインスタンス作成関数
/// </summary>
/// <param name="window_size">設定するウィンドウサイズ構造体</param>
/// <param name="input_">入力機能マネージャークラス参照</param>
/// <returns>ウィンドウインスタンス</returns>
std::unique_ptr<windowInterface> windowFactory::create_window(WindowSize window_size, input::InputStateManager* input_) {

    std::unique_ptr<windowInterface> window_{};

#if defined(_WIN32)
    DEBUG_LOG("windowFactory :: create_window() = WindowsWindow");
    window_ = std::make_unique<WindowsWindow>();
    if (window_->create_window(window_size,input_)) {
        return window_;
    }
#elif defined(__APPLE__)

#elif defined(__linux__)

#else

#endif
    return nullptr;
}