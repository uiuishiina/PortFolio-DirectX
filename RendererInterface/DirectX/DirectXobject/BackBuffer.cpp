#include "BackBuffer.h"

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// バックバッファ作成関数
/// </summary>
/// <param name="device">DirectX12デバイス参照</param>
/// <param name="swapchain">スワップチェインインスタンス</param>
/// <param name="handle">RTVディスクリプタヒープハンドル</param>
/// <param name="buffer_index">対応するスワップチェーンバッファインデックス</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT BackBuffer::create_back_buffer(
	ID3D12Device* device, 
	IDXGISwapChain4* swapchain,
	D3D12_CPU_DESCRIPTOR_HANDLE handle, 
	UINT buffer_index
) {

	rtv_handle = handle;

	//	スワップチェーンからバックバッファを取得し、レンダーターゲットとして保存
	const auto hr = swapchain->GetBuffer(buffer_index, IID_PPV_ARGS(&resource_));
	if (FAILED(hr)) {
		return hr;
	}

	//	レンダーターゲットビューを作成
	D3D12_RENDER_TARGET_VIEW_DESC rtv_desc{};

	DXGI_SWAP_CHAIN_DESC1 swap_desc{};
	if (SUCCEEDED(swapchain->GetDesc1(&swap_desc))) {
		rtv_desc.Format = swap_desc.Format;
	}
	else {
		rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	}

	rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	device->CreateRenderTargetView(resource_.Get(), &rtv_desc, rtv_handle);

	return hr;
}