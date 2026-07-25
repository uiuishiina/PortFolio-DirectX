#pragma once
#include"TextureResouce.h"

/*

	今回のプロジェクトはオブジェクトをクラスに一つだけ用意する目的で作成

*/

///====================================================================
/// RenderTarget クラス
///====================================================================

//@brief === レンダーターゲットクラス ===
class RenderTarget final: public TextureResouce
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	RenderTarget() = default;
	~RenderTarget() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== レンダーターゲット作成関数 ===
	//@param	swapchain	スワップチェインインスタンス
	//@param	handle	RTVディスクリプタヒープハンドル
	//@return	作成の成否
	[[nodiscard]] HRESULT create_render_target(ID3D12Device* device, IDXGISwapChain4* swapchain, 
		D3D12_CPU_DESCRIPTOR_HANDLE handle, UINT buffer_index);

	//@brief	=== RTVハンドル取得関数 ===
	//@return	RTV CPUハンドル
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_rtv_handle() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================
	
	//@brief	== レンダーターゲットディスクリプタハンドル ==
	D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle{};
};