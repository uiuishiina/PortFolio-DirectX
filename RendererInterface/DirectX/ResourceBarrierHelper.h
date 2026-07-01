#pragma once
#include<d3d12.h>

///====================================================================
/// ResourceBarrierHelper クラス
///====================================================================

//@brief	=== リソースバリア作成ヘルパークラス ===
class ResourceBarrierHelper final
{
public:
	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== リソースバリア作成関数 ===
	//@param	resource	リソースバリアを作成するリソース
	//@param	from	リソースの現在の状態
	//@param	to		リソースの遷移先の状態
	//@return	作成されたリソースバリア
	static [[nodiscard]] D3D12_RESOURCE_BARRIER create_resource_barrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) noexcept;
};