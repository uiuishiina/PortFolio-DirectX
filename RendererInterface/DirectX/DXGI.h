#pragma once
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>

///====================================================================
/// DXGIクラス
///====================================================================

//@brief	=== DirectX Graphics Interface ===
class DXGI final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	DXGI() = default;
	~DXGI() = default;
	
	//コピー禁止,ムーブ禁止
	DXGI(const DXGI&) = delete;
	DXGI& operator=(const DXGI&) = delete;
	DXGI(DXGI&&) = delete;
	DXGI& operator=(DXGI&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================
	
	//@brief	=== DXGI初期化関数 ===
	//@return	初期化の成否
	[[nodiscard]] HRESULT initialize_DXGI();

	//@brief	=== DXGIファクトリーインスタンス取得関数 ===
	[[nodiscard]] IDXGIFactory6* get_DXGI_factory() const noexcept;
	
	//@brief	=== DXGIアダプターインスタンス取得関数 ===
	[[nodiscard]] IDXGIAdapter1* get_DXGI_adaptor() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== DXGIファクトリーインスタンス ==
	//@details	DirectXオブジェクトを生成するためのファクトリーインスタンス
	Microsoft::WRL::ComPtr<IDXGIFactory6> factory_{};

	//@brief	== DXGIアダプターインスタンス ==
	//@details	
	Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter_{};

	///====================================================================
	/// Private メンバー関数
	///====================================================================
	
	//@brief	=== DXGIファクトリー作成関数 ===
	//@return	作成の成否
	[[nodiscard]] HRESULT create_DXGI_factory();

	//@brief	=== DXGIアダプター作成関数 ===
	//@return	作成の成否
	[[nodiscard]] HRESULT create_DXGI_adaptor();
};