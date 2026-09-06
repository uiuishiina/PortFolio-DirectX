#pragma once
#include"GPUResource.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクト設定名前空間
		/// </summary>
		namespace desc {
			
			/// <summary>
			/// デプスバッファ設定構造体
			/// </summary>
			struct DepthBufferDesc {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// バッファの横幅
				/// </summary>
				UINT64 width = 1;

				/// <summary>
				/// バッファの縦幅
				/// </summary>
				UINT height = 1;

				/// <summary>
				/// バッファのフォーマット
				/// </summary>
				DXGI_FORMAT format = DXGI_FORMAT_D32_FLOAT;

				/// <summary>
				/// ピクセルごとのサンプル数
				/// </summary>
				UINT sample_count = 1;

				/// <summary>
				/// クリア時のデプス値
				/// </summary>
				float clear_depth = 1.0f;

				/// <summary>
				/// クリア時のステンシル値
				/// </summary>
				UINT8 clear_stencil = 0;

			};
		}

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// デプスバッファクラス
			/// </summary>
			class DepthBuffer final : public GPUResourceBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DepthBuffer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~DepthBuffer() = default;

				
				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// デプスバッファ作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="handle">DSVディスクリプタヒープハンドル</param>
				/// <param name="desc">デプスバッファ設定</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_depth_buffer(
					ID3D12Device* device, 
					D3D12_CPU_DESCRIPTOR_HANDLE handle, 
					desc::DepthBufferDesc& desc
				);

				/* -- 取得関数 -- */

				/// <summary>
				/// DSVハンドル取得関数
				/// </summary>
				/// <returns>DSV CPUハンドル</returns>
				[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_dsv_handle()const noexcept;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// デプスバッファディスクリプタピープハンドル
				/// </summary>
				D3D12_CPU_DESCRIPTOR_HANDLE	dsv_handle{};

			};
		}
	}
}