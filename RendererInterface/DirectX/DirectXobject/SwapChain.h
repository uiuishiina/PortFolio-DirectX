#pragma once
#include"NonMovable.h"
#include"../../../windowInterface/windowInterface.h"
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>


///====================================================================
/// SwapChain クラス
///====================================================================

//@brief === スワップチェーンクラス ===
class SwapChain final : public NonMovableBase
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	SwapChain() = default;
	~SwapChain() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== SwapChain作成関数 ===
	//@param	factory		DirectX12 ファクトリ
	//@param	command_queue	DirectX12 コマンドキュー
	//@param	size		スワップチェーンのサイズ
	//@param	hwnd		ウィンドウハンドル
	//@param	buffer_size	スワップチェーンのバッファ数
	//@return	作成の成否
	[[nodiscard]] HRESULT create_swapchain(IDXGIFactory6* factory,
		ID3D12CommandQueue* command_queue,WindowSize size, HWND hwnd, UINT buffer_size);

	//@brief	=== スワップチェーン取得関数 ===
	//@return	スワップチェーンインスタンス
	[[nodiscard]] IDXGISwapChain4* get_swapchain() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== スワップチェーンインスタンス ==
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain_{};
};