

/* ========== Includeファイル ========== */

#include "GPUResourceHelper.h"
#include"../External/d3dx12.h"

using namespace DirectX::Helper;

/* ========== Publicメンバー関数 ========== */

/* ===== 実行関数 ===== */

/// <summary>
/// UpdateSubResource関数
/// </summary>
/// <param name="list_">コマンドリスト参照</param>
/// <param name="default_resource">コピー先 Default用GPU_Resource参照</param>
/// <param name="upload_resource">コピー元 Upload用GPU_Resource参照</param>
/// <param name="offset">コピー開始位置オフセット</param>
/// <param name="first_subresource">コピー開始Resourceデータインデックス</param>
/// <param name="num_resources">コピーResource数</param>
/// <param name="data">コピーResourceデータ参照</param>
/// <returns>コピーできたサイズ</returns>
[[nodiscard]] UINT64 GPUResourceHelper::update_subresource(
	ID3D12GraphicsCommandList* list_,
	ID3D12Resource* default_resource,
	ID3D12Resource* upload_resource,
	UINT64 offset,
	UINT first_subresource,
	UINT num_resources,
	const D3D12_SUBRESOURCE_DATA* data
) {

	return UpdateSubresources(
		list_,
		default_resource,
		upload_resource,
		offset,
		first_subresource,
		num_resources,
		data
	);
}


/* ===== 取得関数 ===== */

/// <summary>
/// UpdateResourceサイズ取得関数
/// </summary>
/// <param name="default_resource">コピー先 Default用GPU_Resource参照</param>
/// <param name="first_subresource">コピー開始Resourceデータインデックス</param>
/// <param name="num_resources">コピーResource数</param>
/// <returns>コピーに必要なUpdateResourceサイズ</returns>
[[nodiscard]] UINT64 GPUResourceHelper::get_required_intermediate_size(
	ID3D12Resource* default_resource,
	UINT first_subresource,
	UINT num_resources
) {

	return GetRequiredIntermediateSize(
		default_resource, 
		first_subresource, 
		num_resources
	);
}