#include "UploadBufferResource.h"

using namespace render::dx12::object;

/* ==================================================================== */
// Protectedメンバー関数
/* ==================================================================== */

/* -- リソース利用関数 -- */

/// <summary>
/// バッファリソースMap関数
/// </summary>
/// <returns>Mapの成否</returns>
[[nodiscard]] HRESULT UploadBufferResource::map_buffer() {

	return resource_->Map(0, nullptr, &mapped_);
}

/// <summary>
/// バッファリソースUnmap関数
/// </summary>
void UploadBufferResource::unmap_buffer() {

	resource_->Unmap(0, nullptr);
}

/* -- 書き込み関数 -- */

/// <summary>
/// データUpload関数
/// </summary>
/// <param name="src">コピーするデータの先頭ポインター</param>
/// <param name="size">コピーするメモリサイズ</param>
void UploadBufferResource::Upload(const void* src, size_t size) {
	memcpy(mapped_, src, size);
}