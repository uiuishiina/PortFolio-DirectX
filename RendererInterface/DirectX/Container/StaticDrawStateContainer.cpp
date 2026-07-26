#include "StaticDrawStateContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 描画設定作成関数 ===
//@param	key_name	登録するキーの名前
//@param	desc	描画設定
//@return	作成の成否
[[nodiscard]] bool StaticDrawStateContainer::create_draw_state(const std::string& key_name,desc::DrawStateDesc& desc) {

    //  登録済みか確認
    auto hash = get_hash_key(key_name);
    if (hash.has_value()) {
        return true;
    }

    //  描画設定作成
    auto state = std::make_unique<state::Drawstate>();
    if (!state->creaate_draw_state(desc)) {
        return false;
    }

    //  mapに登録
    auto new_hash = allocate_hash(key_name);
    state_map.emplace(new_hash, std::move(state));
    return true;
}


//@brief	=== 描画設定取得関数 ===
//@param	key	描画設定と紐づけたキー
//@return	描画設定クラスインスタンス
[[nodiscard]] render::dx12::state::Drawstate* StaticDrawStateContainer::get_draw_state(UINT key)const noexcept {

    const auto it = state_map.find(key);
    if (it == state_map.end()) {
        return nullptr;
    }
    return it->second.get();
}

//@brief	=== 描画設定取得関数オーバーロード ===
//@param	key_name	描画設定と紐づけたキーの名前
//@return	描画設定クラスインスタンス
[[nodiscard]] render::dx12::state::Drawstate* StaticDrawStateContainer::get_draw_state(const std::string& key_name)const noexcept {

    //  キーを取得
    auto hash = get_hash_key(key_name);
    if (!hash.has_value()) {
        return nullptr;
    }

    //  上の関数に処理を任せる
    return get_draw_state(hash.value());
}