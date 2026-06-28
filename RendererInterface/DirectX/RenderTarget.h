#pragma once
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>

/*

	今回のプロジェクトはオブジェクトをクラスに一つだけ用意する目的で作成

*/

///====================================================================
/// RenderTarget クラス
///====================================================================

//@brief === RenderTarget クラス ===
class RenderTarget final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	RenderTarget() = default;
	~RenderTarget() = default;

	//コピー禁止,ムーブ禁止
	RenderTarget(const RenderTarget&) = delete;
	RenderTarget& operator=(const RenderTarget&) = delete;
	RenderTarget(RenderTarget&&) = delete;
	RenderTarget& operator=(RenderTarget&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	
	[[nodiscard]] bool create_render_target(IDXGISwapChain4* swapchain, ID3D12DescriptorHeap* heap, UINT descriptor_size, UINT buffer_size);

	//@brief	=== RTVハンドル取得関数 ===
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_rtv_handle() const noexcept;

	[[nodiscard]] ID3D12Resource* get_render_target() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== RenderTarget インスタンス ==
	Microsoft::WRL::ComPtr<ID3D12Resource> render_target_{};
};