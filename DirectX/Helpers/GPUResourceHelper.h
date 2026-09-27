#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassObject/GPUResource/GPUResourceBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 補助名前空間
	/// </summary>
	namespace Helper {

		/// <summary>
		/// GPUリソース補助クラス
		/// </summary>
		class GPUResourceHelper
		{
		public:
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
			[[nodiscard]] static UINT64 update_subresource(
				ID3D12GraphicsCommandList* list_,
				ID3D12Resource* default_resource,
				ID3D12Resource* upload_resource,
				UINT64 offset,
				UINT first_subresource,
				UINT num_resources,
				const D3D12_SUBRESOURCE_DATA* data
			);

		
			/* ===== 取得関数 ===== */

			/// <summary>
			/// UpdateResourceサイズ取得関数
			/// </summary>
			/// <param name="default_resource">コピー先 Default用GPU_Resource参照</param>
			/// <param name="first_subresource">コピー開始Resourceデータインデックス</param>
			/// <param name="num_resources">コピーResource数</param>
			/// <returns>コピーに必要なUpdateResourceサイズ</returns>
			[[nodiscard]] static UINT64 get_required_intermediate_size(
				ID3D12Resource* default_resource,
				UINT first_subresource,
				UINT num_resources
			);

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			GPUResourceHelper() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~GPUResourceHelper() = default;

		};
	}
}