
/* ========== Includeファイル ========== */

#include"DirectXRenderer.h"

//  App
#include"../Application/ApplicationDataShare.h"

//  DirectX
#include"DirectXContext.h"
#include"DirectXInitializer.h"
#include"DirectXUpdater.h"
#include"DirectXEnder.h"

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
        return false;
    }

    DirectXInitializer initializer{};

    desc::InitializeDesc desc_{};

    desc_.context_ = context_.get();
    desc_.share_p = shera_p;
    desc_.back_buffer_size = back_buffer_size;
    desc_.frame_resource_size = frame_resource_size;
    desc_.core_ = Initialize::desc::CoreDesc{ hwnd_ ,width,height };
    //desc_.pass_ = Initialize::desc::PassDesc{
    //};

    if (!initializer.initialize(
        desc_
    )) {
        return false;
    }

    return true;
}

/* ===== 実行関数 ===== */

void DirectXRenderer::update_renderer() {

    frame_count++;

    if (!updator_->begin_update()) {
        DEBUG_ERROR_LOG("DirectXRenderer :: update_renderer :: begin_update() = false");
    }

    updator_->sync_frame_resource();

    updator_->reset_frame_resource();

    updator_->update();

    updator_->execute_command_lists();

    updator_->present();

    updator_->end_update();

}

/* ===== 終了関数 ===== */

void DirectXRenderer::end_renderer() {

    DirectXEnder::end(context_.get());

    DEBUG_LOG("Frame_Count = ", frame_count);
}