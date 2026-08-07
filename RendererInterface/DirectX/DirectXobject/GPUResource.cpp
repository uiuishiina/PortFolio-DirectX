#include "GPUResource.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== リソース作成関数 ===
//@param	device	DirectX12 デバイス
//@param	desc	GPUリソース設定構造体
//@return	作成の成否
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

//@brief	=== リソース作成オーバーロード関数 ===
//@param	device		DirectX12 デバイス
//@param	desc		GPUリソース設定構造体
//@param	resource	作成するリソース先参照
//@return	作成の成否
[[nodiscard]] HRESULT GPUResourceBase::create_committed_resource(ID3D12Device* device, const desc::ResourceCreateDesc& desc, Microsoft::WRL::ComPtr<ID3D12Resource>& resource) {

	const auto hr = device->CreateCommittedResource(
		&desc.heap_properties,
		desc.heap_flags,
		&desc.resource_desc,
		desc.initial_state,
		desc.clear_value,
		IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));
	return hr;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== リソース取得関数 ===
//@return	リソース参照
[[nodiscard]] ID3D12Resource* GPUResourceBase::get_resource()const noexcept {
	(resource_ && "GPUリソース nullptr");
	return resource_.Get();
}

//@brief	=== リソース設定取得関数 ===
//@return	リソース設定
[[nodiscard]] D3D12_RESOURCE_DESC GPUResourceBase::get_desc() const noexcept {
	(resource_ && "GPUリソース nullptr");
	return resource_->GetDesc();
}

//@brief	=== GPUアドレス取得関数 ===
//@return	GPUアドレス
[[nodiscard]] D3D12_GPU_VIRTUAL_ADDRESS GPUResourceBase::get_GPU_address() const noexcept {
	(resource_ && "GPUリソース nullptr");
	return resource_->GetGPUVirtualAddress();
}
