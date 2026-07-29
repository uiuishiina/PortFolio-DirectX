#include "DepthBuffer.h"
#include"../Factory&Builder&Helper/ResourceCreateDescHelper.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== デプスバッファ作成関数 ===
//@param	device	DirectX12 デバイス
//@param	handle	DSVディスクリプタヒープハンドル
//@param	desc	デプスバッファ設定
//@return	作成の成否
[[nodiscard]] HRESULT DepthBuffer::create_depth_buffer(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE handle, render::dx12::desc::DepthBufferDesc& desc) {

	desc::ResourceCreateDesc resource_desc{};
	resource_desc.heap_properties = helper::ResourceCreateDescHelper::get_heap_properties(D3D12_HEAP_TYPE_DEFAULT);
	resource_desc.heap_flags = D3D12_HEAP_FLAG_NONE;
	resource_desc.resource_desc = helper::ResourceCreateDescHelper::get_tex2D_desc(desc.format, desc.width, desc.height, 1, 1, desc.sample_count,0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	resource_desc.initial_state = D3D12_RESOURCE_STATE_DEPTH_WRITE;

	D3D12_CLEAR_VALUE clearValue{};
	clearValue.Format = desc.format;
	clearValue.DepthStencil.Depth = desc.clear_depth;
	clearValue.DepthStencil.Stencil = desc.clear_stencil;

	resource_desc.clear_value = &clearValue;

	const auto hr = create_committed_resource(device, resource_desc);
	if (FAILED(hr)) {
		return hr;
	}

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = desc.format;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

	device->CreateDepthStencilView(resource_.Get(), &dsvDesc, handle);

	dsv_handle = handle;

	return hr;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== DSVハンドル取得関数 ===
//@return	DSV CPUハンドル
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DepthBuffer::get_dsv_handle()const noexcept {
	assert(resource_ && "DSVリソース nullptr");
	return dsv_handle;
}