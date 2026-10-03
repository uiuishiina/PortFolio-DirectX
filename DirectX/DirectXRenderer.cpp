
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

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
DirectXRenderer::DirectXRenderer() {

    context_ = std::make_unique<DirectXContext>(
        back_buffer_size,
        frame_resource_size
    );

    updator_ = std::make_unique<DirectXUpdator>(
        frame_resource_size,
        context_.get(),
        shera_p
    );
}

/// <summary>
/// デストラクタ
/// </summary>
DirectXRenderer::~DirectXRenderer() = default;


/* ===== 初期化関数 ===== */

[[nodiscard]] bool DirectXRenderer::initialize_renderer(
    HWND hwnd,
    std::uint32_t width,
    std::uint32_t height,
    App::ApplicationDataShare* shera
) {

    //  変数保存

    hwnd_ = hwnd;
    shera_p = shera;

    if (!hwnd_ || !shera_p) {
        DEBUG_ERROR_LOG("DirectXRenderer :: initialize_renderer() pointer nullptr");
        return false;
    }


    /* ========== 描画機能初期化 ========== */
    
    DirectXInitializer initializer{};

    desc::InitializeDesc desc_{};

    /* ===== Core ===== */
    desc_.context_ = context_.get();
    desc_.share_p = shera_p;
    desc_.back_buffer_size = back_buffer_size;
    desc_.frame_resource_size = frame_resource_size;
    desc_.core_ = Initialize::desc::CoreDesc{ hwnd_ ,width,height };

    /* ===== Shader ===== */
    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::NormalVertex
        ));
    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::NormalPixel
        ));
    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::ColorVertex
        ));
    desc_.shader_.emplace(
        make_shader_desc(
            Resource::Shaders::ColorPixel
        ));

    /* ===== Pipline ===== */
    desc_.pipline_.emplace_root(
        make_root_desc(
            Resource::RootSignatures::Normal
        ));
    desc_.pipline_.emplace_root(
        make_root_desc(
            Resource::RootSignatures::Color
        ));

    desc_.pipline_.emplace_pipline(
        make_pipline_desc(
            Resource::PiplineStates::Normal
        ));
    desc_.pipline_.emplace_pipline(
        make_pipline_desc(
            Resource::PiplineStates::Color
        ));

    /* ===== Resources ===== */
    desc_.resource_.emplace_mesh_desc(
        std::move(Resource::DrawObject::Mesh::NormalMesh)
    );
    desc_.resource_.emplace_mesh_desc(
        std::move(Resource::DrawObject::Mesh::ColorMesh)
    );


    /* ===== 機能初期化 ===== */

    if (!initializer.initialize(
        desc_
    )) {
        return false;
    }


    /* ========== 描画パス初期化 ========== */

    /* ===== Pass ===== */
    Initialize::desc::PassDesc passDesc{};

    passDesc.emplace_command_pass(
        Resource::Pass::Commands::Begin
    );

    passDesc.emplace_command_pass(
        Resource::Pass::Commands::Clear
    );

    passDesc.emplace_command_pass(
        Resource::Pass::Commands::SetView
    );

    passDesc.emplace_draw_object_pass(
        Resource::Pass::DrawObject::NormalTest
    );
    passDesc.emplace_draw_object_pass(
        Resource::Pass::DrawObject::ColorTest
    );


    passDesc.emplace_pipline_pass(
        Resource::Pass::Piplines::ColorTest
    );


    passDesc.emplace_command_pass(
        Resource::Pass::Commands::End
    );

    /* ===== パス初期化 ===== */

    initializer.initialize_pass(
        desc_.context_,
        passDesc
    );


    /* ========== 描画パス設定 ========== */

    DEBUG_LOG(
        HandyItems::Debug::const_str::LineBreak, 
        "========== PassName =========="
    );
    auto passCount = 0;

    for (auto& name : initializer.pass_list) {
        updator_->set_pass(context_->pass_container->get_pass(
            Container::PassKey(name.c_str())
        ));

        DEBUG_LOG(++passCount, " = ", name);
    }
   
    return true;
}

/* ===== 実行関数 ===== */

void DirectXRenderer::update_renderer() {

    frame_count++;

    if (!updator_->begin_update()) {
        DEBUG_ERROR_LOG("DirectXRenderer :: update_renderer :: begin_update() = false");
        return;
    }

    updator_->sync_frame_resource();

    updator_->reset_frame_resource();

    updator_->update();

    updator_->apply_pass();

    updator_->execute_command_lists();

    updator_->present();

    updator_->end_update();

}

/* ===== 終了関数 ===== */

void DirectXRenderer::end_renderer() {

    DirectXEnder::end(context_.get());

    DEBUG_LOG("Frame_Count = ", frame_count);
}