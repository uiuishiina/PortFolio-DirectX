#include "DrawState.h"

using namespace render::dx12::state;

///====================================================================
/// 初期化関数
///====================================================================

//@breif	=== 描画設定作成関数 ===
//@param	desc	描画設定補助構造体
//@return	作成の成否
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

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 描画パス実行時バインド関数 ===
//@param	resouce	描画リソース
void Drawstate::apply(resouces::DrawResouces& resouce) {

    auto* list = resouce.graphics_list;

    list->RSSetViewports(1, &viewport_);
    list->RSSetScissorRects(1, &rect_);

    list->SetGraphicsRootSignature(root_signature);
    list->SetPipelineState(pipeline_state);
}