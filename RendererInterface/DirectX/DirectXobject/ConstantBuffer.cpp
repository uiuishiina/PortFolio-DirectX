#include "ConstantBuffer.h"
#include"../Factory&Builder&Helper/ResourceCreateDescHelper.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// コンスタントバッファ作成関数
/// </summary>
/// <param name="device">DirectX12デバイス参照</param>
/// <param name="handles">CBVディスクリプタヒープハンドル構造体</param>
/// <param name="size">コピーするメモリサイズ</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT ConstantBuffer::create_constant_buffer(
	ID3D12Device* device, 
	render::dx12::utility::Descripter_Handles& handles, 
	size_t size
) {

	//	アラインメント
	const auto size_ = (sizeof(size) + 255) & ~255;

	desc::ResourceCreateDesc resource_desc{};
	resource_desc.heap_properties = helper::ResourceCreateDescHelper::get_heap_properties(D3D12_HEAP_TYPE_UPLOAD);
	resource_desc.heap_flags = D3D12_HEAP_FLAG_NONE;
	resource_desc.resource_desc = helper::ResourceCreateDescHelper::get_buffer_desc(size_);
	resource_desc.initial_state = D3D12_RESOURCE_STATE_GENERIC_READ;

	const auto hr = create_committed_resource(device, resource_desc);
	if (FAILED(hr)) {
		return hr;
	}

	//コンスタントバッファビュー設定
	D3D12_CONSTANT_BUFFER_VIEW_DESC Desc{};
	Desc.BufferLocation = resource_->GetGPUVirtualAddress();
	Desc.SizeInBytes = size_;

	//コンスタントバッファビューとディスクリプターヒープを紐づけ
	device->CreateConstantBufferView(&Desc, handles.cpu_handle);

	gbv_handle = handles.gpu_handle;

	return hr;
}

/* -- 取得関数 -- */

/// <summary>
/// CBVハンドル取得関数
/// </summary>
/// <returns>CBV CPUハンドル</returns>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE ConstantBuffer::get_cbv_handle()const noexcept {
	assert(resource_ && "CBVリソース nullptr");
	return gbv_handle;
}