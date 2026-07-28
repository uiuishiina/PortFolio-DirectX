#include "BufferResource.h"

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== バッファリソースMap関数 ===
//@param	ptr	Map先ポインター
//@return	Mapの成否
[[nodiscard]] HRESULT BufferResource::map_buffer(void** ptr) {

	return resource_->Map(0, nullptr, ptr);
}

//@brief	=== バッファリソースUnmap関数 ===
void BufferResource::unmap_buffer() {

	resource_->Unmap(0, nullptr);
}

//@brief	=== バッファリソースコピー関数 ===
//@param	src	コピーするデータの先頭ポインター
//@param	size	コピーするメモリサイズ
//@return	コピーの成否
[[nodiscard]] HRESULT BufferResource::copy_buffer(const void* src, size_t size) {

	void* mapped = nullptr;
	const auto hr = resource_->Map(0, nullptr, &mapped);
	if (FAILED(hr)) {
		return hr;
	}
	memcpy(mapped, src, size);
	resource_->Unmap(0, nullptr);

	return hr;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== GPUアドレス取得関数 ===
//@return	GPUアドレス
[[nodiscard]] D3D12_GPU_VIRTUAL_ADDRESS BufferResource::get_GPU_address() const noexcept {
	(resource_ && "GPUリソース nullptr");
	return resource_->GetGPUVirtualAddress();
}

