#include "DrawState.h"

using namespace render::dx12::state;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// 描画設定作成関数
/// </summary>
/// <param name="desc">描画設定補助構造体</param>
/// <returns>作成の成否</returns>
[[nodiscard]] bool Drawstate::creaate_draw_state(desc::DrawStateDesc& desc)
{
    if (!desc.root_signature || !desc.pipline_state) {
        return false;
    }
    root_signature = desc.root_signature;
    pipeline_state = desc.pipline_state;
    viewport_ = desc.viewport_;
    rect_ = desc.rect_;

    return true;
}

/// <summary>
/// 描画パス実行時バインド関数
/// </summary>
/// <param name="resouce"></param>
void Drawstate::apply(resources::DrawResources& resouce) {

    auto* list = resouce.graphics_list;

    list->RSSetViewports(1, &viewport_);
    list->RSSetScissorRects(1, &rect_);

    list->SetGraphicsRootSignature(root_signature);
    list->SetPipelineState(pipeline_state);
}