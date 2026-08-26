#include "ConstantBuffer.h"
#include"../Factory&Builder&Helper/ResourceCreateDescHelper.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== コンスタントバッファ作成関数 ===
//@param	device	DirectX12 デバイス
//@param	handles	CBVディスクリプタヒープハンドル構造体
//@param	src		コピーするデータの先頭ポインター
//@param	size	コピーするメモリサイズ
//@return	作成の成否
[[nodiscard]] HRESULT ConstantBuffer::create_constant_buffer(ID3D12Device* device, render::dx12::utility::Descripter_Handles& handles, const void* src, size_t size) {

	const auto size_ = (sizeof(size) + 255) & ~255;

	desc::ResourceCreateDesc resource_desc{};
	resource_desc.heap_properties = helper::ResourceCreateDescHelper::get_heap_properties(D3D12_HEAP_TYPE_UPLOAD);
	resource_desc.heap_flags = D3D12_HEAP_FLAG_NONE;
	resource_desc.resource_desc = helper::ResourceCreateDescHelper::get_buffer_desc(size_);
	resource_desc.initial_state = D3D12_RESOURCE_STATE_GENERIC_READ;

	auto hr = create_committed_resource(device, resource_desc);
	if (FAILED(hr)) {
		return hr;
	}

	//コンスタントバッファビュー設定
	D3D12_CONSTANT_BUFFER_VIEW_DESC Desc{};
	Desc.BufferLocation = resource_->GetGPUVirtualAddress();
	Desc.SizeInBytes = size_;

	//コンスタントバッファビューとディスクリプターヒープを紐づけ
	device->CreateConstantBufferView(&Desc, handles.cpu_handle);

	cbv_handle = handles.gpu_handle;

	hr = map_buffer();
	if (FAILED(hr)) {
		return hr;
	}

	Upload(src, size);

	return hr;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== CBVハンドル取得関数 ===
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE ConstantBuffer::get_cbv_handle()const noexcept {
	assert(resource_ && "CBVリソース nullptr");
	return cbv_handle;
}

//@brief	=== データUpload関数 ===
//@param	src		コピーするデータの先頭ポインター
//@param	size	コピーするメモリサイズ
void ConstantBuffer::upload_constant_buffer(const void* src, size_t size) {
	Upload(src, size);
}