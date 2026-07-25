#include "TextureResouce.h"
#include"../Factory&Builder&Helper/ResourceBarrierHelper.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== リソースバリア遷移関数 ===
//@param	list	描画用コマンドリスト
//@param	next_state	遷移先バリアステート
void  TextureResouce::barrier_transition(ID3D12GraphicsCommandList* list, D3D12_RESOURCE_STATES next_state) {

    assert(resouce_ && "リソース nullptr");
    if (current_state == next_state) {
        return;
    }
    auto barrier = helper::ResourceBarrierHelper::create_resource_barrier(resouce_.Get(),
        current_state, next_state);
    list->ResourceBarrier(1, &barrier);
    current_state = next_state;
}

//@breif	=== リソースインスタンス取得関数 ===
//@return	リソースインスタンス
[[nodiscard]] ID3D12Resource* TextureResouce::get_resouce()const noexcept {
    assert(resouce_ && "リソース nullptr");
    return resouce_.Get();
}