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

//@brief	=== リソース設定作成関数 ===
//@param	format			バッファフォーマット設定
//@param	width			バッファの横幅
//@param	height			バッファの縦幅
//@param	arraySize		バッファの数
//@param	mipLevels		ミップマップの数
//@param	sampleCount		サンプラーの数
//@param	sampleQuality	サンプラークオリティー
//@param	D3D12_RESOURCE_FLAGS	バッファリソースフラグ
//@param	D3D12_TEXTURE_LAYOUT	テクスチャレイアウト設定
//@param	alignment				バッファアラインメント設定
//@return	作成したリソース設定
[[nodiscard]] D3D12_RESOURCE_DESC ResourceCreateDescHelper::get_tex2D_desc(DXGI_FORMAT format, UINT64 width, UINT height,
	UINT16 arraySize, UINT16 mipLevels, UINT sampleCount, UINT sampleQuality,
	D3D12_RESOURCE_FLAGS flags, D3D12_TEXTURE_LAYOUT layout,
	UINT64 alignment) {

	return CD3DX12_RESOURCE_DESC::Tex2D(format, width, height, arraySize, mipLevels, sampleCount, sampleQuality, flags, layout, alignment);
}
