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
		/// GPUリソース設定構造体作成補助クラス
		/// </summary>
		class GPUResourceDescHelper
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ヒーププロパティ設定作成関数
			/// </summary>
			/// <param name="type">ヒープタイプ設定</param>
			/// <returns>作成したヒーププロパティ設定</returns>
			[[nodiscard]] static D3D12_HEAP_PROPERTIES get_heap_properties(
				D3D12_HEAP_TYPE type
			);

			/// <summary>
			/// Bufferリソース設定作成関数
			/// </summary>
			/// <param name="T_buffer_size">バッファメモリサイズ</param>
			/// <returns>作成したリソース設定</returns>
			[[nodiscard]] static D3D12_RESOURCE_DESC get_buffer_desc(
				UINT64 T_buffer_size
			);

			/// <summary>
			/// 2DTextureリソース設定作成関数
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
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			GPUResourceDescHelper() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~GPUResourceDescHelper() = default;

		};
	}
}