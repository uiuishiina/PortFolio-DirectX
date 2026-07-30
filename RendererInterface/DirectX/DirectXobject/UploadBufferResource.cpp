#include "UploadBufferResource.h"

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== バッファリソースMap関数 ===
//@param	ptr	Map先ポインター
//@return	Mapの成否
[[nodiscard]] HRESULT UploadBufferResource::map_buffer() {

	return resource_->Map(0, nullptr, &mapped_);
}

//@brief	=== バッファリソースUnmap関数 ===
void UploadBufferResource::unmap_buffer() {

	resource_->Unmap(0, nullptr);
}

//@brief	=== データUpload関数 ===
void UploadBufferResource::Upload(const void* src, size_t size) {
	memcpy(mapped_, src, size);
}