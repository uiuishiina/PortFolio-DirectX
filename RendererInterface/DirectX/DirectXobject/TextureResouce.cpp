#include "TextureResouce.h"
#include"../Factory&Builder&Helper/ResourceBarrierHelper.h"

//@brief	=== リソースバリア遷移関数 ===
//@param	list	描画用コマンドリスト
//@param	next_state	遷移先バリアステート
void  TextureResouce::barrier_transition(ID3D12GraphicsCommandList* list, D3D12_RESOURCE_STATES next_state) {

    if (current_state == next_state) {
        return;
    }
    auto barrier = ResourceBarrierHelper::create_resource_barrier(resouce_.Get(),
        current_state, next_state);
    list->ResourceBarrier(1, &barrier);
    current_state = next_state;
}

//@breif	=== リソースインスタンス取得関数 ===
//@return	リソースインスタンス
[[nodiscard]] ID3D12Resource* TextureResouce::get_resouce()const noexcept {
    return resouce_.Get();
}