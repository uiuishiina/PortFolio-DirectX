#include"RenderTarget.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== コンストラクタ ===
//@details	基底クラスの引数付きコンストラクタを呼び出し,バックバッファから取得したものは最初Presentになっている
RenderTarget::RenderTarget() : TextureResource(D3D12_RESOURCE_STATE_PRESENT) {};

//@brief	=== レンダーターゲット作成関数 ===
//@param	swapchain	スワップチェインインスタンス
//@param	handle	RTVディスクリプタヒープハンドル
//return	作成の成否
[[nodiscard]] HRESULT RenderTarget::create_render_target(ID3D12Device* device, IDXGISwapChain4* swapchain,
	D3D12_CPU_DESCRIPTOR_HANDLE handle, UINT buffer_index) {

	rtv_handle = handle;

	//	スワップチェーンからバックバッファを取得し、レンダーターゲットとして保存
	const auto hr = swapchain->GetBuffer(buffer_index, IID_PPV_ARGS(&resource_));
	if (FAILED(hr)) {
		return hr;
	}

	//	レンダーターゲットビューを作成
	D3D12_RENDER_TARGET_VIEW_DESC rtv_desc{};
	rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	device->CreateRenderTargetView(resource_.Get(), &rtv_desc, rtv_handle);

	return hr;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== RTVハンドル取得関数 ===
//@return	RTV_CPUハンドル
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::get_rtv_handle() const noexcept {
	assert(resource_ && "レンダーターゲット nullptr");
	return rtv_handle;
}
