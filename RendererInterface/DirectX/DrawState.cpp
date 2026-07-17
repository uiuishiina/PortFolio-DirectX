#include "DrawState.h"

//@breif	=== 描画設定作成関数 ===
//@param	desc	描画設定補助構造体
//@return	作成の成否
[[nodiscard]] bool render::state::Drawstate::creaate_draw_state(DrawStateDesc& desc)
{
    if (!desc.root_signature || !desc.pipline_state) {
        return false;
    }
    root_signature = desc.root_signature;
    pipline_state = desc.pipline_state;
    viewport_ = desc.viewport_;
    rect_ = desc.rect_;

    return true;
}

//@brief	=== 描画設定セット関数 ===
//@param	list	描画用コマンドリスト
void render::state::Drawstate::set_draw_state(ID3D12GraphicsCommandList* list) {

    list->RSSetViewports(1, &viewport_);
    list->RSSetScissorRects(1, &rect_);

    list->SetGraphicsRootSignature(root_signature);
    list->SetPipelineState(pipline_state);
}