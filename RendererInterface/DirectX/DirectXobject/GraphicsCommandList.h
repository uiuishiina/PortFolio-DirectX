#pragma once
#include<d3d12.h>
#include<wrl/client.h>

///====================================================================
/// CommandList クラス
///====================================================================

//@brief	=== 描画用コマンドリストクラス ===
class GraphicsCommandList final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//	コンストラクタ,デストラクタ
	GraphicsCommandList() = default;
	~GraphicsCommandList() = default;

	//	コピー禁止,ムーブ禁止
	GraphicsCommandList(const GraphicsCommandList&) = delete;
	GraphicsCommandList& operator=(const GraphicsCommandList&) = delete;
	GraphicsCommandList(GraphicsCommandList&&) = delete;
	GraphicsCommandList& operator=(GraphicsCommandList&&) = delete;

	///====================================================================
	/// Private メンバー関数
	///====================================================================

	//@brief	=== 描画用コマンドリスト作成関数 ===
	//@param	device	DirectX12 デバイス
	//@param	type	コマンドリストタイプ
	//@param	allocator	コマンドアロケータインスタンス
	//@return	作成の成否
	[[nodiscard]] HRESULT create_graphics_command_list(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* allocator);

	//@brief	=== 描画用コマンドリスト取得関数 ===
	//@return	コマンドリストインスタンス
	[[nodiscard]] ID3D12GraphicsCommandList* get_graphics_command_list() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== 描画用コマンドリストインスタンス ==
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list_{};
};