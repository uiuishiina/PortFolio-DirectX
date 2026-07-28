#include "ResourceCreateDescHelper.h"
#include"../AddFile/d3dx12.h"

using namespace render::dx12::helper;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== ヒーププロパティ設定作成関数 ===
//@param	type	ヒープタイプ設定
//@return	作成したヒーププロパティ設定
[[nodiscard]] D3D12_HEAP_PROPERTIES ResourceCreateDescHelper::get_heap_properties(D3D12_HEAP_TYPE type) {
	return CD3DX12_HEAP_PROPERTIES(type);
}

//@brief	=== リソース設定作成関数 ===
//@param	T_buffer_size	バッファメモリサイズ
//@return	作成したリソース設定
[[nodiscard]] D3D12_RESOURCE_DESC ResourceCreateDescHelper::get_buffer_desc(UINT T_buffer_size) {
	return CD3DX12_RESOURCE_DESC::Buffer(T_buffer_size);
}