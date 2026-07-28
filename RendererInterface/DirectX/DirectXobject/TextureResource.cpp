#include "TextureResource.h"
#include"../Factory&Builder&Helper/ResourceBarrierHelper.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化時処理
///====================================================================

//@brief	=== 引数付きコンストラクタ ===
//@param	state	初期設定リソースステート
TextureResource::TextureResource(D3D12_RESOURCE_STATES state) {
    current_state = state;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== リソースバリア遷移関数 ===
//@param	list	描画用コマンドリスト
//@param	next_state	遷移先バリアステート
void  TextureResource::barrier_transition(ID3D12GraphicsCommandList* list, D3D12_RESOURCE_STATES next_state) {

    assert(resource_ && "リソース nullptr");
    if (current_state == next_state) {
        return;
    }
    auto barrier = helper::ResourceBarrierHelper::create_resource_barrier(resource_.Get(),
        current_state, next_state);
    list->ResourceBarrier(1, &barrier);
    current_state = next_state;
}