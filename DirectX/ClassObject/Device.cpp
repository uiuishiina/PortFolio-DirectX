
/* ========== Includeファイル ========== */

#include "Device.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

#include"Debug/DebugLogSystem.h"

using namespace DirectX::ClassObject;

/* ========== Publicメンバー関数 ========== */

/* ===== 初期化関数 ===== */

/// <summary>
/// デバイス作成関数
/// </summary>
/// <param name="adapter_">DXGIアダプター参照</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT Device::create_device(
	IDXGIAdapter1* adapter_
) {

	for (auto& level : levels_) {
		device_ = select_level(adapter_, level.first);
		if (device_) {
			DEBUG_LOG("Device level = ", level.second);
			return S_OK;
		}
	}
	return E_FAIL;
}

/* ========== Privateメンバー関数 ========== */

/* ===== 初期化関数 ===== */

/// <summary>
/// レベル選択関数
/// </summary>
/// <param name="adapter_">DXGIアダプター参照</param>
/// <param name="level">D3D機能レベル</param>
/// <returns>作成したDevice... 失敗なら[ nullptr ]</returns>
[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Device> Device::select_level(
	IDXGIAdapter1* adapter_,
	D3D_FEATURE_LEVEL level
) {

	Microsoft::WRL::ComPtr<ID3D12Device> device;

	//	D3D12デバイスの作成を試みる
	const auto hr = D3D12CreateDevice(
		adapter_,				//	使用するDXGIアダプターポインタ
		level,					//	要求する機能レベル
		IID_PPV_ARGS(&device)	//	ID3D12Deviceインターフェースのポインタを受け取る
	);

	if (FAILED(hr)) {
		return nullptr; // デバイスの作成に失敗した場合はnullptrを返す
	}

	return device; // デバイスの作成に成功した場合はデバイスインスタンスを返す
}