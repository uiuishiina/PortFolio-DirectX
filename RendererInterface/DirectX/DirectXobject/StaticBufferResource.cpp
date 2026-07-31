#include "StaticBufferResource.h"

using namespace render::dx12::object;

//@brief	=== バッファリソースコピー関数 ===
//@param	src	コピーするデータの先頭ポインター
//@param	size	コピーするメモリサイズ
//@return	コピーの成否
[[nodiscard]] HRESULT StaticBufferResource::copy_buffer(const void* src, size_t size) {

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
[[nodiscard]] D3D12_GPU_VIRTUAL_ADDRESS StaticBufferResource::get_GPU_address() const noexcept {
	(resource_ && "GPUリソース nullptr");
	return resource_->GetGPUVirtualAddress();
}

