#include "TextureResource.h"
#include"../Factory&Builder&Helper/ResourceBarrierHelper.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// クラス設定
/* ==================================================================== */

/// <summary>
/// 引数付きコンストラクタ
/// </summary>
/// <param name="state">初期設定リソースステート</param>
TextureResource::TextureResource(D3D12_RESOURCE_STATES state) {
    current_state = state;
}

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// リソースバリア遷移関数
/// </summary>
/// <param name="list">描画用コマンドリスト参照</param>
/// <param name="next_state">遷移先バリアステート</param>
void  TextureResource::barrier_transition(
    ID3D12GraphicsCommandList* list, 
    D3D12_RESOURCE_STATES next_state
) {

    assert(resource_ && "リソース nullptr");
    if (current_state == next_state) {
        return;
    }
    //  リソースバリア遷移
    auto barrier = helper::ResourceBarrierHelper::create_resource_barrier(resource_.Get(),
        current_state, next_state);
    list->ResourceBarrier(1, &barrier);
    current_state = next_state;

}