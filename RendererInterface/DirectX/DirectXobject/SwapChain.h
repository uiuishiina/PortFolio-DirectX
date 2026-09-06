#pragma once
#include"Others/NonCopyableBase.h"
#include"../../../windowInterface/windowInterface.h"
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>

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
			/// スワップチェーンクラス
			/// </summary>
			class SwapChain final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				SwapChain() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~SwapChain() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// SwapChain作成関数
				/// </summary>
				/// <param name="factory">DXGIファクトリー参照</param>
				/// <param name="command_queue">コマンドキュー参照</param>
				/// <param name="size">スワップチェーンサイズ設定</param>
				/// <param name="hwnd">ウィンドウハンドル</param>
				/// <param name="buffer_size">スワップチェーンバッファ数</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_swapchain(
					IDXGIFactory6* factory,
					ID3D12CommandQueue* command_queue, 
					WindowSize size, 
					HWND hwnd, 
					UINT buffer_size
				);

				/* -- 取得関数 -- */

				/// <summary>
				/// スワップチェーン取得関数
				/// </summary>
				/// <returns>スワップチェーン参照</returns>
				[[nodiscard]] IDXGISwapChain4* get_swapchain() const noexcept;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// スワップチェーンインスタンス
				/// </summary>
				Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain_{};

			};
		}
	}
}