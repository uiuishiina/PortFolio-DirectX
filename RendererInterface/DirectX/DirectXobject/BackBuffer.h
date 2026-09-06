#pragma once
#include"RenderTarget.h"

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
			/// バックバッファ派生クラス
			/// </summary>
			class BackBuffer final : public RenderTarget
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				BackBuffer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~BackBuffer() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// バックバッファ作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="swapchain">スワップチェインインスタンス</param>
				/// <param name="handle">RTVディスクリプタヒープハンドル</param>
				/// <param name="buffer_index">対応するスワップチェーンバッファインデックス</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_back_buffer(
					ID3D12Device* device, 
					IDXGISwapChain4* swapchain,
					D3D12_CPU_DESCRIPTOR_HANDLE handle, 
					UINT buffer_index
				);

			};
		}
	}
}