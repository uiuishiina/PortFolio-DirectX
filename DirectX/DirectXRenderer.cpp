
/* ========== Includeファイル ========== */

#include"DirectXRenderer.h"

//  App
#include"../Application/ApplicationDataShare.h"

//  DirectX
#include"DirectXContext.h"
#include"DirectXInitializer.h"

#include"Debug/DebugLogSystem.h"

using namespace DirectX;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
DirectXRenderer::DirectXRenderer() {
    context_.register_unique(std::make_unique<DirectXContext>());
}

/// <summary>
/// デストラクタ
/// </summary>
DirectXRenderer::~DirectXRenderer() = default;

[[nodiscard]] bool DirectXRenderer::initialize_renderer(
    HWND hwnd,
    App::ApplicationDataShare* shera
) {

    //  変数保存

    hwnd_ = hwnd;
    shera_p = shera;

    DirectXInitializer initializer{};

    if (!initializer.initialize(context_.get())) {
        return false;
    }

    return true;
}

/* ===== 実行関数 ===== */

void DirectXRenderer::update_renderer() {

}

/* ===== 終了関数 ===== */

void DirectXRenderer::end_renderer() {

}