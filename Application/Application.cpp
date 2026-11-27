
/* ========== Includeファイル ========== */

#include"Application.h"
#include"Debug/DebugLogSystem.h"
#include"SystemComfig.h"
#include"System/RendererPipeline/MeshPipeline.h"
#include"System/CreateResourceFunc/CompileShaderFunc.h"
#include"System/CreateResourceFunc/CreateMeshFunc.h"
#include"System/CreateResourceFunc/CreateCameraFunc.h"

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

    D3D12_VIEWPORT viewport{};
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = 1280;
    viewport.Height = 720;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1;

    D3D12_RECT scissorRect{};
    scissorRect.left = 0;
    scissorRect.top = 0;
    scissorRect.right = 1280;
    scissorRect.bottom = 720;

    renderer->add_resource_func(
        CreateCameraFunc::create_camera_func(
            "MainCamera",
            viewport,
            scissorRect
        )
    );

    struct NormalVector {
        float pos[3] = {};
    };

    renderer->add_resource_func(
        CreateMeshFunc::create_mesh_func(
            "NormalMesh",
            CreateMeshFunc::MeshDesc<NormalVector>
        {
            .vertex_ = {
                {	-0.5f,	-0.5f,	0.5f},
                {		0,	 0.5f,	0.5f},
                {	 0.5f,	-0.5f,	0.5f}
            },
            .index_ = {
                    0,1,2
            }
        }
        )
    );

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

    auto* entity = system_.get_system<EntityManager>();
    auto* player = entity->create_entity("Player");
    auto* camera = entity->create_entity("Camera");
    
    if (player->add_component(
        system_.create_component<RendererComponent>(player)
    ))
    {
        player->add_component(
            system_.create_component<MeshComponent>("NormalMesh")
        );
    }

    if (camera->add_component(
        system_.create_component<CameraComponent>("MainCamera")
    ))
    {
        auto* renderer = system_.get_system<RendererSystem>();
        renderer->set_main_camera(
            camera->get_component<CameraComponent>()->get_camera()
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