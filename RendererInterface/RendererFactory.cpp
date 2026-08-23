#include"RendererFactory.h"
#include"DirectXRenderer.h"
#include"../Debug/DebugLogSystem.h"

std::unique_ptr<RendererInterface> RendererFactory::create_renderer(windowInterface* window, sharedData::ApplicationSharedData* shared_datas) {
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