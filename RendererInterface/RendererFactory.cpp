#include"RendererFactory.h"
#include"DirectXRenderer.h"
#include"../Debug/DebugLogSystem.h"

using namespace render;

/// <summary>
/// 描画機能作成関数
/// </summary>
/// <param name="window">ウィンドウインターフェースクラス参照</param>
/// <param name="shared_datas">プリケーションデータシェアクラス参照</param>
/// <returns>作成した描画機能インスタンス</returns>
std::unique_ptr<RendererInterface> RendererFactory::create_renderer(window::windowInterface* window, sharedData::ApplicationSharedData* shared_datas) {

    std::unique_ptr<RendererInterface> renderer_{};

#if defined(_WIN32)
    DEBUG_LOG("RendererFactory :: create_renderer() = DirectXRenderer");
    renderer_ = std::make_unique<DirectXRenderer>();
    if (renderer_->create_renderer(window,shared_datas)) {
        return renderer_;
    }
#elif defined(__APPLE__)

#elif defined(__linux__)

#else

#endif
    return nullptr;
}