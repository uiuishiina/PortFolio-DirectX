
/* ========== Includeファイル ========== */

#include"Application.h"
#include"Debug/DebugLogSystem.h"

#include"ApplicationClock.h"

using namespace App;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
Application::Application() {

    const std::uint32_t FPS = 60;    //  ミリ秒換算
    
    clock_ = std::make_unique<ApplicationClock>(1000 / FPS);

    DEBUG_LOG("Application :: Application()");
}

/// <summary>
/// デストラクタ
/// </summary>
Application::~Application() {
    DEBUG_LOG("Application :: ~Application()");
}

/* ===== 初期化関数 ===== */

/// <summary>
/// アプリケーション開始関数
/// </summary>
/// <returns>開始したなら [ true ]</returns>
[[nodiscard]] bool Application::start_app() {

    if (!initialize_app()) {
        return false;
    }

    run_app();

    end_app();

    return true;
}

/* ========== Privateメンバー関数 ========== */

/* ===== 初期化関数 ===== */

/// <summary>
/// アプリケーション初期化関数
/// </summary>
/// <returns>初期化の成否</returns>
[[nodiscard]] bool Application::initialize_app() {

    DEBUG_LOG(
        HandyItems::Debug::const_str::LineBreak,
        "========== initialize =========="
        );

    if (!initialize_window(Windows::WindowSize{ 1280,720 })) {
        return false;
    }
    if (!initialize_renderer()) {
        return false;
    }

    return true;
}

/// <summary>
/// ウィンドウ初期化関数
/// </summary>
/// <param name="size">ウィンドウサイズ</param>
/// <returns>初期化の成否</returns>
[[nodiscard]] bool Application::initialize_window(
    const Windows::WindowSize& size
) {

    const auto value = main_window.initialize_window(
        size,
        &data_share
    );
    if (!value) {
        DEBUG_LOG("Window :: initialize_window() = false");
    }

    return value;
}

/// <summary>
/// 描画機能初期化関数
/// </summary>
/// <returns>初期化の成否</returns>
[[nodiscard]] bool Application::initialize_renderer() {

    const auto [w, h] = main_window.get_size();

    const auto value = main_renderer.initialize_renderer(
        main_window.get_hwnd(),
        w,
        h,
        &data_share
    );
    if (!value) {
        DEBUG_LOG("DirectXRenderer :: initialize_renderer() = false");
    }

    return value;
}

/* ===== 実行関数 ===== */

/// <summary>
/// アプリケーション実行関数
/// </summary>
void Application::run_app() {

    DEBUG_LOG(
        HandyItems::Debug::const_str::LineBreak,
        "========== run =========="
    );

    bool foucs_{};

    clock_->initialize_clock();

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

        const auto skip = clock_->wait_fixed_to_skip(5);
        if (skip > 5) {
            DEBUG_LOG("clock_ skip = ", skip);
        }

        {
            auto foucs = main_window.get_focus();
            if (foucs_ != foucs) {
                DEBUG_LOG("Window Foucs = ", (foucs ? "ON" : "OFF"));
                foucs_ = foucs;
            }
            if (!foucs) {
                continue;
            }
        }

        main_renderer.update_renderer();
    }
}

/* ===== 終了時関数 ===== */

/// <summary>
/// アプリケーション終了処理関数
/// </summary>
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