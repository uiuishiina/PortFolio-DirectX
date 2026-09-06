#pragma once
#include"UploadBufferResource.h"
#include"ResourceUtility.h"
#include<vector>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// コンスタントバッファ派生クラス
			/// </summary>
			class ConstantBuffer final : public UploadBufferResource
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				ConstantBuffer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~ConstantBuffer() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// コンスタントバッファ作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="handles">CBVディスクリプタヒープハンドル構造体</param>
				/// <param name="size">コピーするメモリサイズ</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_constant_buffer(ID3D12Device* device, utility::Descripter_Handles& handles, size_t size);


				/* -- 取得関数 -- */

				/// <summary>
				/// CBVハンドル取得関数
				/// </summary>
				/// <returns>CBV CPUハンドル</returns>
				[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE get_cbv_handle()const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				/// <summary>
				/// コンスタントバッファディスクリプターハンドル
				/// </summary>
				D3D12_GPU_DESCRIPTOR_HANDLE gbv_handle{};

			};
		}
	}
}