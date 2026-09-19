
/* ========== Includeファイル ========== */

#include"Application.h"
#include"Debug/DebugLogSystem.h"

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

    DEBUG_LOG(
        HandyItems::Debug::const_str::LineBreak,
        "========== initialize =========="
        );

    if (!initialize_window({ 1280,720 })) {
        return false;
    }
    if (!initialize_renderer()) {
        return false;
    }

    DEBUG_LOG("Application :: initialize_app() = true");
    return true;
}


void Application::run_app() {

    DEBUG_LOG(
        HandyItems::Debug::const_str::LineBreak,
        "========== run =========="
    );

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

        main_renderer.update_renderer();
    }
}


[[nodiscard]] bool Application::initialize_window(
    const Windows::WindowSize& size
) {

    const auto value = main_window.initialize_window(
        size,
        &data_share
    );

    DEBUG_LOG(
        "Window :: initialize_window() = ",
        value ? "true" : "false"
    );
    return value;
}

[[nodiscard]] bool Application::initialize_renderer() {

    const auto value = main_renderer.initialize_renderer(
        main_window.get_hwnd(),
        &data_share
    );

    DEBUG_LOG(
        "DirectXRenderer :: initialize_renderer() = ",
        value ? "true" : "false"
        );
    return value;
}
    

/* ===== 終了時関数 ===== */

void Application::end_app() {

    DEBUG_LOG(
        HandyItems::Debug::const_str::LineBreak,
        "========== end =========="
    );

    do {
        main_window.pull_event();
    } while (!main_window.completed_destroy());

    main_renderer.end_renderer();
}