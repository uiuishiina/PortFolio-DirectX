#include"SwapChain.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== スワップチェーン作成関数 ===
//@param	factory		DirectX12 ファクトリ
//@param	command_queue	DirectX12 コマンドキュー
//@param	size		スワップチェーンのサイズ
//@param	hwnd		ウィンドウハンドル
//@param	buffer_size	Sワップチェーンのバッファ数
//@return	作成の成否
[[nodiscard]] HRESULT SwapChain::create_swapchain(IDXGIFactory6* factory,
	ID3D12CommandQueue* command_queue, WindowSize size, HWND hwnd, UINT buffer_size) {

	//	スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapchain_desc{};
	swapchain_desc.Width = size.width;
	swapchain_desc.Height = size.height;
	swapchain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchain_desc.Stereo = FALSE;
	swapchain_desc.SampleDesc.Count = 1;
	swapchain_desc.SampleDesc.Quality = 0;
	swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchain_desc.BufferCount = buffer_size;
	swapchain_desc.Scaling = DXGI_SCALING_STRETCH;
	swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchain_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchain_desc.Flags = 0;

	//	スワップチェーンの作成
	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapchain1{};
	const auto hr = factory->CreateSwapChainForHwnd(command_queue, hwnd, &swapchain_desc, nullptr, nullptr, &swapchain1);
	if (FAILED(hr)) {
		return hr;
	}

	//	スワップチェーンをIDXGISwapChain4にキャスト
	return swapchain1.As(&swapchain_);
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== スワップチェーン取得関数 ===
//@return	スワップチェーン参照
[[nodiscard]] IDXGISwapChain4* SwapChain::get_swapchain() const noexcept {
	assert(swapchain_ && "スワップチェーン nullptr");
	return swapchain_.Get();
}