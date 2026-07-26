#include "StaticRenderTargetStateContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 描画パス用レンダーターゲット設定作成関数 ==
//@param	key_name	登録するキーの名前
//@param	slots	登録するターゲットの種類配列
//@return	作成の成否
[[nodiscard]] bool StaticRenderTargetStateContainer::create_render_target_state(const std::string& key_name, const std::vector<RenderTargetSlot>& slots) {

    //  登録済みか確認
    auto hash = get_hash_key(key_name);
    if (hash.has_value()) {
        return false;
    }

    //  レンダーターゲット設定
    auto state = std::make_unique<state::DrawRenderTargetState>();
    for (auto& p : slots) {
        state->add_render_target_slot(p);
    }

    //  mapに登録
    auto new_hash = allocate_hash(key_name);
    render_target_state_map.emplace(new_hash, std::move(state));
    return true;
}

//@brief	=== 描画パス用レンダーターゲット設定取得関数 ===
//@param	key	描画パス用レンダーターゲット設定と紐づけたキー
//@return	描画パス用レンダーターゲット設定クラス参照
[[nodiscard]] render::dx12::state::DrawRenderTargetState* StaticRenderTargetStateContainer::get_draw_state(UINT key)const noexcept {

    const auto it = render_target_state_map.find(key);
    if (it == render_target_state_map.end()) {
        return nullptr;
    }
    return it->second.get();
}

//@brief	=== 描画パス用レンダーターゲット設定取得関数オーバーロード ===
//@param	key_name	描画パス用レンダーターゲット設定と紐づけたキーの名前
//@return	描画パス用レンダーターゲット設定クラス参照
[[nodiscard]] render::dx12::state::DrawRenderTargetState* StaticRenderTargetStateContainer::get_draw_state(const std::string& key_name)const noexcept {

    auto hash = get_hash_key(key_name);
    if (!hash.has_value()) {
        return nullptr;
    }
    return get_draw_state(hash.value());
}