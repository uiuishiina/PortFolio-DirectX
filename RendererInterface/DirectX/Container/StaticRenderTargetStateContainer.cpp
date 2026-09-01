#include "StaticRenderTargetStateContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数
///====================================================================


/// <summary>
/// 描画パス用レンダーターゲット設定作成関数
/// </summary>
/// <param name="key"></param>
/// <param name="render_target_slots"></param>
/// <param name="depth_slot"></param>
/// <returns></returns>
[[nodiscard]] bool StaticRenderTargetStateContainer::create_render_target_state(const handle::RenderTargetStateKey& key, const std::vector<RenderTargetSlot>& render_target_slots, std::optional<DepthSlot> depth_slot) {

    
    //  レンダーターゲット設定
    auto state = std::make_unique<state::DrawRenderTargetState>();
    for (auto& p : render_target_slots) {
        state->add_render_target_slot(p);
    }

    if (depth_slot.has_value()) {
        state->set_depth(depth_slot.value());
    }

    //  mapに登録
    return add_value(key, std::move(state));
}