#include"ResourceBarrierHelper.h"

using namespace render::dx12::helper;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// リソースバリア作成関数
/// </summary>
/// <param name="resource">リソースバリアを作成するリソース</param>
/// <param name="from">リソースの現在の状態</param>
/// <param name="to">リソースの遷移先の状態</param>
/// <returns>作成されたリソースバリア</returns>
[[nodiscard]] D3D12_RESOURCE_BARRIER ResourceBarrierHelper::create_resource_barrier(
	ID3D12Resource* resource,
	D3D12_RESOURCE_STATES from, 
	D3D12_RESOURCE_STATES to
) noexcept {

	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = resource;
	barrier.Transition.StateBefore = from;
	barrier.Transition.StateAfter = to;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	return barrier;
}