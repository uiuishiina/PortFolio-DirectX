
/* ========== Includeファイル ========== */

#include"Application.h"
#include"Debug/DebugLogSystem.h"

#include"ApplicationClock.h"
#include"System/ClockSystem.h"
#include"System/InputSystem.h"

using namespace App;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
Application::Application() {

    const std::uint32_t FPS = 60;    //  ミリ秒換算

    system_.register_system<ClockSystem>(1000 / FPS);
    system_.register_system<EntityManager>();
    system_.register_system<InputSystem>();

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
        size
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

    if (system_.init_systems())
    {
        
    }

    auto* player = system_.get_system<EntityManager>()->create_entity("player");
    player->add_component(
        system_.create_component<InputComponent>()
    );
    system_.get_system<InputSystem>()->get_action_manager().add_action_bind(
        InputAction::Esc,
        InputKeyBoard::Esc
    );

    auto* clock = system_.get_system<ClockSystem>();

    if (clock) {
        clock->start_clock();
    }

    ClockSystem::Milliseconds delta_time{};
    std::uint32_t fps_count{};

    while (true)
    {
        system_.update_system();

        main_window.pull_event();

        if (main_window.get_closed()) {
            break;
        }

        if (clock) {

            const auto skip = clock->wait_fixed_to_skip(5);
            if (skip > 5) {
                DEBUG_LOG("clock_ skip = ", skip);
            }

            delta_time += clock->get_delta_time();
            ++fps_count;

            if (delta_time >= ClockSystem::Milliseconds{ 1000 }) {

                delta_time -= ClockSystem::Milliseconds{ 1000 };
                main_window.set_text(std::wstring{ L"FPS = " + std::to_wstring(fps_count) }.c_str());
                fps_count = 0;
            }

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

        if (player->get_component<InputComponent>()->get_action_state(InputAction::Esc) == ActionState::Down)
        {
            main_window.close_window();
            continue;
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