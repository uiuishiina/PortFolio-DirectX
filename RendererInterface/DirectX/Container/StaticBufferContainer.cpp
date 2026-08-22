#include"StaticBufferContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== リソース取得関数 ===
//@param	key		リソースと紐づけたキー
//@return	リソースクラス参照
[[nodiscard]] render::dx12::object::StaticBufferResource* StaticBufferContainer::get_resource(UINT key)const noexcept {

    //  登録済みか確認
    const auto it = buffer_map.find(key);
    if (it == buffer_map.end()) {
        return nullptr;
    }
    return it->second.get();
}