
/* ========== Includeファイル ========== */

#include"Application.h"
#include"Debug/DebugLogSystem.h"
#include"SystemComfig.h"
#include"System/RendererPipeline/MeshPipeline.h"

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
    auto* renderer = system_.get_system<RendererSystem>();
    renderer->add_pipeline<NormalMeshPipeline>();
}

/// <summary>
/// デストラクタ
/// </summary>
Application::~Application() {

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

    if (!system_.init_systems())
    {
        return false;
    }

    if (
        auto* debug = system_.get_system<DebugSystem>();
        debug
        )
    {
        debug->debug_log(
            HandyItems::Debug::const_str::LineBreak,
            "========== initialize_app =========="
        );
    }
    
    return true;
}

/* ===== 実行関数 ===== */

/// <summary>
/// アプリケーション実行関数
/// </summary>
void Application::run_app() {

    if (
        auto* debug = system_.get_system<DebugSystem>();
        debug
        )
    {
        debug->debug_log(
            HandyItems::Debug::const_str::LineBreak,
            "========== run_app =========="
        );
    }

    loop_.run();
}

/* ===== 終了時関数 ===== */

/// <summary>
/// アプリケーション終了処理関数
/// </summary>
void Application::end_app() {


    if (
        auto* debug = system_.get_system<DebugSystem>();
        debug
        )
    {
        debug->debug_log(
            HandyItems::Debug::const_str::LineBreak,
            "========== end_app =========="
        );
    }
}