#include"Device.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== Device初期化関数 ===
//@param	adapter_	DXGIアダプター参照
//@return	初期化の成否
[[nodiscard]] HRESULT Device::initialize_Device(IDXGIAdapter1* adapter_) {

	for (const auto& level : levels) {
		device_ = create_device(adapter_, level);
		if (device_) {	
			return S_OK;
		}
	}
	return E_FAIL;
}

//@brief	=== Device作成関数 ===
//@param	adapter_	DXGIアダプター参照
//@param	featureLevel	D3D機能レベル
//@return	Deviceインスタンス
Microsoft::WRL::ComPtr<ID3D12Device> Device::create_device(
	IDXGIAdapter1* adapter_, D3D_FEATURE_LEVEL featureLevel) {
	
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

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== Device取得関数 ===
//@return	Device参照
[[nodiscard]] ID3D12Device* Device::get_device() const noexcept {
	assert(device_ && "Device nullptr");
	return device_.Get();
}