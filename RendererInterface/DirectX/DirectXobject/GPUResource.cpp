#include "GPUResource.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */


/// <summary>
/// リソース取得関数
/// </summary>
/// <returns>リソース参照</returns>
[[nodiscard]] ID3D12Resource* GPUResourceBase::get_resource()const noexcept {
	assert(resource_ && "GPUリソース nullptr");
	return resource_.Get();
}


/* ==================================================================== */
// Protectedメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// リソース作成関数
/// </summary>
/// <param name="device">DirectX12デバイス参照</param>
/// <param name="desc">GPUリソース設定構造体</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT GPUResourceBase::create_committed_resource(ID3D12Device* device, const desc::ResourceCreateDesc& desc) {

	const auto hr = device->CreateCommittedResource(
		&desc.heap_properties,
		desc.heap_flags,
		&desc.resource_desc,
		desc.initial_state,
		desc.clear_value,
		IID_PPV_ARGS(resource_.ReleaseAndGetAddressOf()));
	return hr;
}

/// <summary>
/// リソース作成関数 
/// </summary>
/// <details>
/// 追加でリソースが必要な場合に [メンバー変数以外] のリソースを作成できる関数
/// </details>
/// <param name="device">DirectX12デバイス参照</param>
/// <param name="desc">GPUリソース設定構造体</param>
/// <param name="resource">作成するリソース先参照</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT GPUResourceBase::create_committed_resource(
	ID3D12Device* device, 
	const desc::ResourceCreateDesc& desc, 
	Microsoft::WRL::ComPtr<ID3D12Resource>& resource
) {

	return device->CreateCommittedResource(
		&desc.heap_properties,
		desc.heap_flags,
		&desc.resource_desc,
		desc.initial_state,
		desc.clear_value,
		IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));
}

/* -- 取得関数 -- */

/// <summary>
/// リソース設定取得関数
/// </summary>
/// <returns>リソース設定</returns>
[[nodiscard]] D3D12_RESOURCE_DESC GPUResourceBase::get_desc() const noexcept {

	assert(resource_ && "GPUリソース nullptr");
	return resource_->GetDesc();
}

/// <summary>
/// GPUアドレス取得関数
/// </summary>
/// <returns>GPUアドレス</returns>
[[nodiscard]] D3D12_GPU_VIRTUAL_ADDRESS GPUResourceBase::get_GPU_address() const noexcept {

	assert(resource_ && "GPUリソース nullptr");
	return resource_->GetGPUVirtualAddress();
}
