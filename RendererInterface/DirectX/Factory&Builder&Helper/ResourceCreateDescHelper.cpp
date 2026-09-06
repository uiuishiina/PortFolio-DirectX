#include "ResourceCreateDescHelper.h"
#include"../AddFile/d3dx12.h"

using namespace render::dx12::helper;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// ヒーププロパティ設定作成関数
/// </summary>
/// <param name="type">ヒープタイプ設定</param>
/// <returns>作成したヒーププロパティ設定</returns>
[[nodiscard]] D3D12_HEAP_PROPERTIES ResourceCreateDescHelper::get_heap_properties(D3D12_HEAP_TYPE type) {
	return CD3DX12_HEAP_PROPERTIES(type);
}

/// <summary>
/// リソース設定作成関数
/// </summary>
/// <param name="T_buffer_size">バッファメモリサイズ</param>
/// <returns>作成したリソース設定</returns>
[[nodiscard]] D3D12_RESOURCE_DESC ResourceCreateDescHelper::get_buffer_desc(UINT T_buffer_size) {
	return CD3DX12_RESOURCE_DESC::Buffer(T_buffer_size);
}

/// <summary>
/// リソース設定作成関数
/// </summary>
/// <param name="format">バッファフォーマット設定</param>
/// <param name="width">バッファの横幅</param>
/// <param name="height">バッファの縦幅</param>
/// <param name="arraySize">バッファの数</param>
/// <param name="mipLevels">ミップマップの数</param>
/// <param name="sampleCount">サンプラーの数</param>
/// <param name="sampleQuality">サンプラークオリティー</param>
/// <param name="flags">バッファリソースフラグ</param>
/// <param name="layout">テクスチャレイアウト設定</param>
/// <param name="alignment">バッファアラインメント設定</param>
/// <returns>作成したリソース設定</returns>
[[nodiscard]] D3D12_RESOURCE_DESC ResourceCreateDescHelper::get_tex2D_desc(
	DXGI_FORMAT format,
	UINT64 width, 
	UINT height,
	UINT16 arraySize, 
	UINT16 mipLevels, 
	UINT sampleCount, 
	UINT sampleQuality,
	D3D12_RESOURCE_FLAGS flags, 
	D3D12_TEXTURE_LAYOUT layout,
	UINT64 alignment
) {
	return CD3DX12_RESOURCE_DESC::Tex2D(format, width, height, arraySize, mipLevels, sampleCount, sampleQuality, flags, layout, alignment);
}
