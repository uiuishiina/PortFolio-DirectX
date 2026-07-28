#include "VertexBuffer.h"
#include"../Factory&Builder&Helper/ResourceCreateDescHelper.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化処理
///====================================================================

//@brief	=== 頂点バッファ用GPUリソース設定作成 ===
//@param	T_buffer_size	頂点バッファメモリサイズ
//@return	作成した頂点バッファ用GPUリソース設定
[[nodiscard]] render::dx12::desc::ResourceCreateDesc VertexBuffer::create_vertex_buffer_desc(UINT T_buffer_size) {

	desc::ResourceCreateDesc desc{};

	desc.heap_properties = helper::ResourceCreateDescHelper::get_heap_properties(D3D12_HEAP_TYPE_UPLOAD);
	desc.heap_flags = D3D12_HEAP_FLAG_NONE;
	desc.resource_desc = helper::ResourceCreateDescHelper::get_buffer_desc(T_buffer_size);
	desc.initial_state = D3D12_RESOURCE_STATE_GENERIC_READ;

	return desc;
}

///====================================================================
/// 実行時処理
///====================================================================

//@brief	=== 頂点バッファビュー取得関数 ===
//@return	頂点バッファビュー参照
[[nodiscard]] const D3D12_VERTEX_BUFFER_VIEW* VertexBuffer::get_buffer_view()const noexcept {
	assert(resource_ && "頂点バッファリソース nullptr");
	return &vertex_buffer_view;
}