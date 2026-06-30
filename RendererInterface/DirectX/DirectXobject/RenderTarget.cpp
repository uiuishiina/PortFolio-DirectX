#include"RenderTarget.h"

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== レンダーターゲット作成関数 ===
//@param	swapchain	スワップチェインインスタンス
//@param	heap	RTVディスクリプタヒープ
//@param	heap	RTVディスクリプタヒープ
[[nodiscard]] HRESULT RenderTarget::create_render_target(ID3D12Device* device, IDXGISwapChain4* swapchain,
	ID3D12DescriptorHeap* heap, UINT buffer_index) {

	heap->GetDevice(IID_PPV_ARGS(&device));	//	ディスクリプタヒープからデバイスを取得
	rtv_handle = heap->GetCPUDescriptorHandleForHeapStart();	//	ディスクリプタヒープのCPUハンドルを取得

	//	スワップチェーンからバックバッファを取得し、レンダーターゲットとして保存
	const auto hr = swapchain->GetBuffer(buffer_index, IID_PPV_ARGS(&render_target_));
	if (FAILED(hr)) {
		return hr;
	}

	//	レンダーターゲットビューを作成
	D3D12_RENDER_TARGET_VIEW_DESC rtv_desc{};
	rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	device->CreateRenderTargetView(render_target_.Get(), &rtv_desc, rtv_handle);

	return S_OK;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== RTVハンドル取得関数 ===
//@return	RTV CPUハンドル
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::get_rtv_handle() const noexcept {
	return rtv_handle;
}

//@brief	=== レンダーターゲット取得関数 ===
//@return	レンダーターゲットインスタンス
[[nodiscard]] ID3D12Resource* RenderTarget::get_render_target() const noexcept {
	return render_target_.Get();
}