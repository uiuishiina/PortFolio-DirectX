#pragma once
#include"NonMovable.h"
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>

///====================================================================
/// Deviceクラス
///====================================================================

//@brief	=== DirectX Device ===
class Device final :public NonMovableBase
{
public:
	///====================================================================
	///	クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	Device() = default;
	~Device() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================
	
	//@brief	=== Device初期化関数 ===
	//@param	adapter_	DXGIアダプターインスタンス
	//@return	初期化の成否
	[[nodiscard]] HRESULT initialize_Device(IDXGIAdapter1* adapter_);

	//@brief	=== Deviceインスタンス取得関数 ===
	//@return	Deviceインスタンス
	[[nodiscard]] ID3D12Device* get_device() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================
	
	//@brief	== Deviceインスタンス ==
	//@details	DirectXオブジェクトを生成するためのDeviceインスタンス
	Microsoft::WRL::ComPtr<ID3D12Device> device_{};

	//	要求するD3D機能レベルのリスト...DirectX 12.2からDirectX 11.0までの機能レベルを指定
	D3D_FEATURE_LEVEL levels[5] = {
	D3D_FEATURE_LEVEL_12_2,	//	49664
	D3D_FEATURE_LEVEL_12_1,	//	49408
	D3D_FEATURE_LEVEL_12_0,	//	49152
	D3D_FEATURE_LEVEL_11_1,	//	45056
	D3D_FEATURE_LEVEL_11_0	//	40960
	};

	///====================================================================
	/// Private メンバー関数
	///====================================================================
	
	//@brief	=== Device作成関数 ===
	//@param	adapter_	DXGIアダプターインスタンス
	//@param	featureLevel	D3D機能レベル
	//@return	Deviceインスタンス
	Microsoft::WRL::ComPtr<ID3D12Device> create_device(IDXGIAdapter1* adapter_, D3D_FEATURE_LEVEL featureLevel);
};