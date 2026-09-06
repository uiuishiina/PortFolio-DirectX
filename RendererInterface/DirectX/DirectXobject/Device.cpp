#include"Device.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 初期化関数 -- */

/// <summary>
/// Device初期化関数
/// </summary>
/// <param name="adapter_">DXGIアダプター参照</param>
/// <returns>初期化の成否</returns>
[[nodiscard]] HRESULT Device::initialize_Device(IDXGIAdapter1* adapter_) {

	for (const auto& level : levels) {
		device_ = create_device(adapter_, level);
		if (device_) {	
			return S_OK;
		}
	}
	return E_FAIL;
}


/* -- 取得関数 -- */

/// <summary>
/// Device取得関数
/// </summary>
/// <returns>Device参照</returns>
[[nodiscard]] ID3D12Device* Device::get_device() const noexcept {
	assert(device_ && "Device nullptr");
	return device_.Get();
}

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// Device作成関数
/// </summary>
/// <param name="adapter_">DXGIアダプター参照</param>
/// <param name="featureLevel">D3D機能レベル</param>
/// <returns>Deviceインスタンス</returns>
Microsoft::WRL::ComPtr<ID3D12Device> Device::create_device(
	IDXGIAdapter1* adapter_,
	D3D_FEATURE_LEVEL featureLevel
) {

	Microsoft::WRL::ComPtr<ID3D12Device> device;

	//	D3D12デバイスの作成を試みる
	const auto hr = D3D12CreateDevice(
		adapter_,					//	使用するDXGIアダプターポインタ
		featureLevel,				//	要求する機能レベル
		IID_PPV_ARGS(&device)		//	ID3D12Deviceインターフェースのポインタを受け取る
	);
	if (FAILED(hr)) {
		return nullptr; // デバイスの作成に失敗した場合はnullptrを返す
	}

	return device; // デバイスの作成に成功した場合はデバイスポインタを返す
}