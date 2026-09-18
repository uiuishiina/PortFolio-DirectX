
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

[[nodiscard]] bool Application::start_app() {

    if (!initialize_app()) {
        return false;
    }

    run_app();

    end_app();
}

/* ========== Privateメンバー関数 ========== */

/* ===== 初期化関数 ===== */

[[nodiscard]] bool Application::initialize_app() {

    if (!initialize_window({ 1280,720 })) {
        return false;
    }

    DEBUG_LOG("Application :: initialize_app() = true");
    return true;
}


void Application::run_app() {

    while (true)
    {
        data_share.get_input()->update_frame();

        main_window.pull_event();

        if (data_share.get_input()->is_down(HandyItems::input::InputKeyBoard::Esc)) {
            main_window.close_window();
        }

        if (main_window.get_closed()) {
            break;
        }

        if (!main_window.get_focus()) {
            continue;
        }
    }
}


[[nodiscard]] bool Application::initialize_window(
    const Windows::WindowSize& size
) {

    return main_window.initialize_window(size, &data_share);
}

/* ===== 終了時関数 ===== */

void Application::end_app() {

    do {
        main_window.pull_event();
    } while (!main_window.completed_destroy());
}