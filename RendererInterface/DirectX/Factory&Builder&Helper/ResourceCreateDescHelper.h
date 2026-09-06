#pragma once
#include"../DirectXobject/GPUResource.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// Helper名前空間
		/// </summary>
		namespace helper {

			/// <summary>
			/// リソース設定作成ヘルパークラス
			/// </summary>
			class ResourceCreateDescHelper final
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// ヒーププロパティ設定作成関数
				/// </summary>
				/// <param name="type">ヒープタイプ設定</param>
				/// <returns>作成したヒーププロパティ設定</returns>
				[[nodiscard]] static D3D12_HEAP_PROPERTIES get_heap_properties(D3D12_HEAP_TYPE type);

				/// <summary>
				/// リソース設定作成関数
				/// </summary>
				/// <param name="T_buffer_size">バッファメモリサイズ</param>
				/// <returns>作成したリソース設定</returns>
				[[nodiscard]] static D3D12_RESOURCE_DESC get_buffer_desc(UINT T_buffer_size);

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
				[[nodiscard]] static D3D12_RESOURCE_DESC get_tex2D_desc(
					DXGI_FORMAT format, 
					UINT64 width,
					UINT height,
					UINT16 arraySize = 1,
					UINT16 mipLevels = 0, 
					UINT sampleCount = 1,
					UINT sampleQuality = 0, 
					D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE,
					D3D12_TEXTURE_LAYOUT layout = D3D12_TEXTURE_LAYOUT_UNKNOWN, 
					UINT64 alignment = 0
				);

			private:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				ResourceCreateDescHelper() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~ResourceCreateDescHelper() = default;

			};
		}
	}
}