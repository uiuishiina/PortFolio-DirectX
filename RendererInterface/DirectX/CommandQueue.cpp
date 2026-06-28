#include"CommandQueue.h"
#include"AddFile/d3dx12.h"

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== コマンドキュー作成関数 ===
//@param	device	DirectX12 デバイス
//@param	type	コマンドリストタイプ
//@return	作成の成否
[[nodiscard]] HRESULT CommandQueue::create_command_queue(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type) {

	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type		= type;
	desc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags		= D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask	= 0;

	return device->CreateCommandQueue(&desc, IID_PPV_ARGS(&command_queue_));
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== コマンドキュー取得関数 ===
//@return	コマンドキューインスタンス
[[nodiscard]] ID3D12CommandQueue* CommandQueue::get_command_queue() const noexcept {
	return command_queue_.Get();
}