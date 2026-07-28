#include "IndexBuffer.h"
#include"../Factory&Builder&Helper/ResourceCreateDescHelper.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化処理
///====================================================================

//@brief	=== インデックスバッファ用GPUリソース設定作成 ===
//@param	T_buffer_size	インデックスバッファメモリサイズ
//@return	作成したインデックスバッファ用GPUリソース設定
[[nodiscard]] render::dx12::desc::ResourceCreateDesc IndexBuffer::create_index_buffer_desc(UINT T_buffer_size) {

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

//@brief	=== インデックスバッファビュー取得関数 ===
//@return	インデックスバッファビュー参照
[[nodiscard]] const D3D12_INDEX_BUFFER_VIEW* IndexBuffer::get_buffer_view()const noexcept {
	assert(resource_ && "インデックスバッファリソース nullptr");
	return &index_buffer_view;
}