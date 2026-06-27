#pragma once
#include<d3d12.h>
#include<wrl/client.h>

///====================================================================
/// CommandQueue クラス
///====================================================================

//@brief	=== DirectX12 コマンドキュークラス ===
class CommandQueue final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	CommandQueue() = default;
	~CommandQueue() = default;

	//コピー禁止,ムーブ禁止
	CommandQueue(const CommandQueue&) = delete;
	CommandQueue& operator=(const CommandQueue&) = delete;
	CommandQueue(CommandQueue&&) = delete;
	CommandQueue& operator=(CommandQueue&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== コマンドキュー作成関数 ===
	//@param	device	DirectX12 デバイス
	//@param	type	コマンドリストタイプ
	//@return	作成の成否
	[[nodiscard]] HRESULT create_command_queue(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type);
	
	//@brief	=== コマンドキュー取得関数 ===
	//@return	コマンドキューインスタンス
	[[nodiscard]] ID3D12CommandQueue* get_command_queue() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================
	
	//@brief	== コマンドキューインスタンス ==
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> command_queue_{};

};