
/* ========== Includeファイル ========== */

#include"Application.h"
#include"./Debug/DebugLogSystem.h"

using namespace App;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
Application::Application() {
    DEBUG_LOG("Application :: Application()");
}

/// <summary>
/// デストラクタ
/// </summary>
Application::~Application() {
    DEBUG_LOG("Application :: ~Application()");
}

/* ===== 初期化関数 ===== */


[[nodiscard]] bool Application::initialize_app() {

    if (!initialize_window({ 1280,720 })) {
        return false;
    }

    return true;
}


void Application::run_app() {


    end_app();
}


/* ========== Privateメンバー関数 ========== */

/* ===== 初期化関数 ===== */

[[nodiscard]] bool Application::initialize_window(
    const Windows::WindowSize& size
) {

    return main_window.initialize_window(size);
}

/* ===== 終了時関数 ===== */

void Application::end_app() {

}