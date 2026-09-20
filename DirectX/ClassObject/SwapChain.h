#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>

//	その他
#include<cstdint>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// スワップチェーンクラス
		/// </summary>
		class SwapChain final : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			SwapChain() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~SwapChain() = default;
			
			/* ===== 初期化関数 ===== */

			/// <summary>
			/// スワップチェーン作成関数
			/// </summary>
			/// <param name="factory_">DXGIファクトリー参照</param>
			/// <param name="queue_">コマンドキュー参照</param>
			/// <param name="hwnd">ウィンドウハンドル</param>
			/// <param name="width">横幅</param>
			/// <param name="height">縦幅</param>
			/// <param name="buffer_size">スワップチェーン枚数</param>
			/// <param name="format">スワップチェーンフォーマット... 初期設定[ DXGI_FORMAT_R8G8B8A8_UNORM ]</param>
			/// <param name="sample">サンプラー設定... 初期設定[ Count = 1, Quality = 0 ]</param>
			/// <returns></returns>
			[[nodiscard]] HRESULT create_swapchain(
				IDXGIFactory6* factory_,
				ID3D12CommandQueue* queue_,
				HWND hwnd,
				std::uint32_t width,
				std::uint32_t height,
				UINT buffer_size,
				DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM,
				DXGI_SAMPLE_DESC sample = DXGI_SAMPLE_DESC{1,0}
			) {

				//	スワップチェーンの設定
				DXGI_SWAP_CHAIN_DESC1 swapchain_desc{};
				swapchain_desc.Width				= width;
				swapchain_desc.Height				= height;
				swapchain_desc.Format				= format;
				swapchain_desc.Stereo				= FALSE;
				swapchain_desc.SampleDesc			= sample;
				swapchain_desc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapchain_desc.BufferCount			= buffer_size;
				swapchain_desc.Scaling				= DXGI_SCALING_STRETCH;
				swapchain_desc.SwapEffect			= DXGI_SWAP_EFFECT_FLIP_DISCARD;
				swapchain_desc.AlphaMode			= DXGI_ALPHA_MODE_UNSPECIFIED;
				swapchain_desc.Flags				= 0;

				//	スワップチェーン作成
				Microsoft::WRL::ComPtr<IDXGISwapChain1> swapchain1{};
				const auto hr = factory_->CreateSwapChainForHwnd(
					queue_, 
					hwnd, 
					&swapchain_desc, 
					nullptr, 
					nullptr, 
					&swapchain1
				);
				if (FAILED(hr)) {
					return hr;
				}

				//	スワップチェーンをIDXGISwapChain4にキャスト
				return swapchain1.As(&swapchain_);
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// スワップチェーン参照取得関数
			/// </summary>
			/// <returns>スワップチェーン参照</returns>
			[[nodiscard]] IDXGISwapChain4* get() const noexcept {

				return swapchain_.Get();
			}

			/// <summary>
			/// スワップチェーン参照アロー演算子オーバーロード
			/// </summary>
			/// <returns>スワップチェーン参照</returns>
			[[nodiscard]] IDXGISwapChain4* operator -> () const noexcept {

				return get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// スワップチェーンインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain_{};

		};
	}
}