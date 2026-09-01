#include "StaticDrawStateContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数
///====================================================================
/// <summary>
/// 描画設定作成関数
/// </summary>
/// <param name="key">追加したい倫理側のキー</param>
/// <param name="desc">設定する描画設定</param>
/// <returns>作成の成否</returns>
[[nodiscard]] bool StaticDrawStateContainer::create_draw_state(const handle::DrawStateKey& key, desc::DrawStateDesc& desc) {

    //  描画設定作成
    auto state = std::make_unique<state::Drawstate>();
    if (!state->creaate_draw_state(desc)) {
        return false;
    }

    //  mapに登録
    return add_value(key, std::move(state));
}