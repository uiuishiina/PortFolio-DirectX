#include"ResourceBarrierHelper.h"

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== リソースバリア作成関数 ===
//@param	resource	リソースバリアを作成するリソース
//@param	from	リソースの現在の状態
//@param	to		リソースの遷移先の状態
//@return	作成されたリソースバリア
[[nodiscard]] D3D12_RESOURCE_BARRIER ResourceBarrierHelper::create_resource_barrier(ID3D12Resource* resource,
	D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) noexcept {

	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = resource;
	barrier.Transition.StateBefore = from;
	barrier.Transition.StateAfter = to;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	return barrier;
}