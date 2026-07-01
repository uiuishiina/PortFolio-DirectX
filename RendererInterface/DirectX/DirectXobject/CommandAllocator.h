#pragma once
#include<d3d12.h>
#include<wrl/client.h>

///====================================================================
/// CommandAllocator クラス
///====================================================================

//@brief	=== コマンドアロケータクラス ===
class CommandAllocator final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	CommandAllocator() = default;
	~CommandAllocator() = default;

	//コピー禁止,ムーブ禁止
	CommandAllocator(const CommandAllocator&) = delete;
	CommandAllocator& operator=(const CommandAllocator&) = delete;
	CommandAllocator(CommandAllocator&&) = delete;
	CommandAllocator& operator=(CommandAllocator&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== コマンドアロケータ作成関数 ===
	//@param	device	DirectX12 デバイス
	//@param	type	コマンドリストタイプ
	//@return	作成の成否
	[[nodiscard]] HRESULT create_command_allocator(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type);

	//@brief	=== コマンドアロケータリセット関数 ===
	void reset_command_allocator();

	//@brief	=== コマンドアロケータ取得関数 ===
	//@return	コマンドアロケータインスタンス
	[[nodiscard]] ID3D12CommandAllocator* get_command_allocator() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================
		
	//@brief	== コマンドアロケータインスタンス ==
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> command_allocator_{};
};