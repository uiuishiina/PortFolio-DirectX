
/* ========== Includeファイル ========== */

#include"DirectXRenderer.h"

//  App
#include"../Application/ApplicationDataShare.h"

//  DirectX
#include"DirectXContext.h"
#include"DirectXInitializer.h"
#include"DirectXUpdater.h"
#include"DirectXEnder.h"

#include"Resource/CommandList.h"
#include"Resource/ShaderList.h"
#include"Resource/PiplineStateList.h"
#include"Resource/PiplinePassList.h"
#include"Resource/MeshList.h"
#include"Resource/DrawObjectList.h"

#include"Debug/DebugLogSystem.h"

using namespace DirectX;


/* ========== 無名空間 ========== */

namespace {

    template<typename... Args>
    std::vector<std::string> get_pass_name(const Args&... args) {

        std::vector<std::string> pass_names{};

        auto func = [&pass_names](const std::string& name) {
                pass_names.push_back(name);
            };

        (func(args._Myfirst._Val), ...);

        return pass_names;
    }

}

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
DirectXRenderer::DirectXRenderer() = default;

/// <summary>
/// デストラクタ
/// </summary>
DirectXRenderer::~DirectXRenderer() {

    end_renderer();
}

/* ===== 初期化関数 ===== */

/// <summary>
/// 描画機能初期化関数
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
/// <param name="width">ウィンドウの横幅</param>
/// <param name="height">ウィンドウの縦幅</param>
/// <param name="shera_">アプリケーションデータシェアクラス参照</param>
/// <returns>初期化の成否</returns>
[[nodiscard]] bool DirectXRenderer::initialize_renderer(
    HWND hwnd,
    std::uint32_t width,
    std::uint32_t height,
    App::ApplicationDataShare* shera_
) {

    //  変数保存
    hwnd_ = hwnd;
    shera_p = shera_;

    if (!hwnd_ || !shera_p) {
        DEBUG_ERROR_LOG("DirectXRenderer :: initialize_renderer() pointer nullptr");
        return false;
    }

    context_ = std::make_unique<DirectXContext>();
    updator_ = std::make_unique<DirectXUpdator>(context_.get(), shera_p);

    /* ========== 描画機能初期化 ========== */
    
    //  初期化クラス作成
    DirectXInitializer initializer{};

    //  初期化設定作成
    desc::InitializeDesc desc_{};

    /* ===== Main ===== */
    desc_.context_ = context_.get();
    desc_.share_p = shera_p;
    desc_.back_buffer_size = back_buffer_size;
    desc_.frame_resource_size = frame_resource_size;

    /* ===== Core ===== */
    desc_.core_ = Initialize::desc::CoreDesc{ hwnd_ ,width,height };
    
    desc_.core_.emplace_heap_desc(
        { 0, 1, 0, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE }
    );
    desc_.core_.emplace_heap_desc(
        { 0, 1, 0, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE }
    );
    desc_.core_.emplace_heap_desc(
        { 5, 0, 3, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE }
    );
    

    /* ===== Shader ===== */

    /* -- Normal -- */

    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::NormalVertex
        ));
    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::NormalPixel
        ));

    /* -- Color -- */

    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::ColorVertex
        ));
    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::ColorPixel
        ));

    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::ConstantVertex
        ));

    /* ===== Pipline ===== */

    /* -- Root -- */

    desc_.pipline_.emplace_root(
        make_root_desc(
            Resource::RootSignatures::Normal
        ));
    desc_.pipline_.emplace_root(
        make_root_desc(
            Resource::RootSignatures::Color
        ));

    desc_.pipline_.emplace_root(
        make_root_desc(
            Resource::RootSignatures::Constant
        ));

    /* -- PiplineState -- */

    desc_.pipline_.emplace_pipline(
        make_pipline_desc(
            Resource::PiplineStates::Normal
        ));
    desc_.pipline_.emplace_pipline(
        make_pipline_desc(
            Resource::PiplineStates::Color
        ));

    desc_.pipline_.emplace_pipline(
        make_pipline_desc(
            Resource::PiplineStates::Constant
        ));

    /* ===== Resources ===== */

    /* -- Mesh -- */

    desc_.resource_.emplace_mesh_desc(
        std::move(Resource::DrawObject::Mesh::NormalMesh)
    );
    desc_.resource_.emplace_mesh_desc(
        std::move(Resource::DrawObject::Mesh::ColorMesh)
    );
    desc_.resource_.emplace_mesh_desc(
        std::move(Resource::DrawObject::Mesh::NormalBox)
    );


    /* ========== 描画パス初期化 ========== */

    auto& passDesc = desc_.pass_;

    /* -- Begin -- */

    passDesc.emplace_begin_path(
        Resource::Path::Commands::Begin
    );

    /* -- Command -- */

    passDesc.emplace_command_path(
        Resource::Path::Commands::Clear
    );

    passDesc.emplace_command_path(
        Resource::Path::Commands::SetView
    );

    passDesc.emplace_command_path(
        "SetCamera",
        {
            [](ClassModule::FrameContext& frame) {
                

                auto camera = frame.camera_container->get_camera_object(
                    Container::CameraObjectKey{ "MainCamera" }
                );

                //camera->get_camera_transform().rotate({ 0,0.001f,0 });
                camera->update_camera_object();


                camera->set_buffer(
                    0,
                    frame.graphic_list->get()
                );
                camera->set_view_port(
                    frame.graphic_list->get()
                );

                frame.player_->get_transform().translation_.x_ =
                    3 * HandyItems::Math::MathF::sin(HandyItems::Math::MathF::Double_PI / 288 * frame.frame_count);
                frame.player_->get_transform().rotation_ *=
                    HandyItems::Math::MathF::from_axis_angle({ 0,1,0 }, 0.01f);

                frame.player_->update_mesh_object();

                frame.player_->draw(frame.graphic_list->get());
            }
        }
    );
    

    /* -- DrawObject -- */

    passDesc.emplace_draw_object_path(
        Resource::Path::DrawObject::NormalTest
    );
    passDesc.emplace_draw_object_path(
        Resource::Path::DrawObject::ColorTest
    );

    /* -- Pipline -- */

    passDesc.emplace_pipline_path(
        Resource::Path::Piplines::NormalTest
    );
    passDesc.emplace_pipline_path(
        Resource::Path::Piplines::ColorTest
    );

    passDesc.emplace_pipline_path(
        Resource::Path::Piplines::ConstantTest
    );

    /* -- End -- */

    passDesc.emplace_end_path(
        Resource::Path::Commands::End
    );

    if (!initializer.initialize(
        desc_
    )) {
        return false;
    }


    /* ========== 描画パス設定 ========== */


    const auto pass_names = get_pass_name(
        Resource::Path::Commands::Begin,

        Resource::Path::Commands::Clear,
        Resource::Path::Commands::SetView,

        //Resource::Path::Piplines::NormalTest,
        //Resource::Path::DrawObject::NormalTest,

        Resource::Path::Piplines::ColorTest,
        Resource::Path::DrawObject::ColorTest,

        Resource::Path::Piplines::ConstantTest,

        Resource::Path::Commands::End
    );

    DEBUG_LOG(
        HandyItems::Debug::const_str::LineBreak, 
        "========== UsePassName =========="
    );
    auto passCount = 0;

    for (auto& name : pass_names) {
        updator_->set_pass(context_->pass_container->get_pass(
            Container::PathKey(name.c_str())
        ));

        DEBUG_LOG(++passCount, " = ", name);
    }
   
    return true;
}

/* ===== 実行関数 ===== */

/// <summary>
/// 描画機能更新関数
/// </summary>
void DirectXRenderer::update_renderer() {

    if (!updator_->begin_update()) {
        DEBUG_ERROR_LOG("DirectXRenderer :: update_renderer :: begin_update() = false");
        return;
    }

    updator_->sync_frame_resource();

    updator_->reset_frame_resource();

    updator_->update_resource();

    updator_->apply_path();

    updator_->execute_command_lists();

    updator_->present();

    updator_->end_update();

}

/* ===== 終了関数 ===== */

/// <summary>
/// 描画機能終了時処理関数
/// </summary>
void DirectXRenderer::end_renderer() {

    DirectXEnder::end(context_.get());
}