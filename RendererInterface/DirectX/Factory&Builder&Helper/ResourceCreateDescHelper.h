#pragma once
#include"../DirectXobject/GPUResource.h"

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// Helper名前空間
		///====================================================================

		namespace helper {

			class ResourceCreateDescHelper final
			{
			public:
				///====================================================================
				/// P+ublic メンバー関数
				///====================================================================

				//@brief	=== ヒーププロパティ設定作成関数 ===
				//@param	type	ヒープタイプ設定
				//@return	作成したヒーププロパティ設定
				static [[nodiscard]] D3D12_HEAP_PROPERTIES get_heap_properties(D3D12_HEAP_TYPE type);

				//@brief	=== リソース設定作成関数 ===
				//@param	T_buffer_size	バッファメモリサイズ
				//@return	作成したリソース設定
				static [[nodiscard]] D3D12_RESOURCE_DESC get_buffer_desc(UINT T_buffer_size);

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
				static [[nodiscard]] D3D12_RESOURCE_DESC get_tex2D_desc(DXGI_FORMAT format, UINT64 width, UINT height,
					UINT16 arraySize = 1, UINT16 mipLevels = 0, UINT sampleCount = 1, UINT sampleQuality = 0, 
					D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE,D3D12_TEXTURE_LAYOUT layout = D3D12_TEXTURE_LAYOUT_UNKNOWN, 
					UINT64 alignment = 0);

			private:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				ResourceCreateDescHelper() = default;
				~ResourceCreateDescHelper() = default;

			};
		};
	};
};