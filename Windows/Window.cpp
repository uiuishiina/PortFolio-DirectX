
/* ========== Includeファイル ========== */

#include"Window.h"
#include"./Debug/DebugLogSystem.h"

using namespace Windows;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
Window::Window() {
    DEBUG_LOG("Window :: Window()");
}

/// <summary>
/// デストラクタ
/// </summary>
Window::~Window() {
    DEBUG_LOG("Window :: ~Window()");
}

/* ===== 初期化関数 ===== */

[[nodiscard]] bool Window::initialize_window(
    const WindowSize& size
) {

    size_ = size;

    return true;
}