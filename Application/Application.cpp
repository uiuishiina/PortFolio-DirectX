
/* ========== Includeファイル ========== */

#include"Application.h"
#include"Debug/DebugLogSystem.h"

#include"System/ClockSystem.h"
#include"System/InputSystem.h"
#include"System/WindowsSystem.h"
#include"System/DebugSystem.h"
#include"System/RendererSystem.h"

using namespace App;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
Application::Application() {

    const std::uint32_t FPS = 60;    //  ミリ秒換算

    system_.register_systems<EntityManager, InputSystem, DebugSystem>();
    system_.register_system<ClockSystem>(1000 / FPS);
    system_.register_system<WindowsSystem>(Windows::WindowSize{ 1280,720 });
    system_.register_system<RendererSystem>();

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

    if (!system_.init_systems())
    {
        return false;
    }

    return true;
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

    loop_.run();
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
}