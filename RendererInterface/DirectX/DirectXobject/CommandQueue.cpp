#include"CommandQueue.h"
#include"../AddFile/d3dx12.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// コマンドキュー作成関数
/// </summary>
/// <param name="device">DirectX12デバイス参照</param>
/// <param name="type">コマンドリストタイプ</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT CommandQueue::create_command_queue(
	ID3D12Device* device, 
	D3D12_COMMAND_LIST_TYPE type
) {

	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type		= type;
	desc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags		= D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask	= 0;

	return device->CreateCommandQueue(&desc, IID_PPV_ARGS(&command_queue));
}

/* -- 取得関数 -- */

/// <summary>
/// コマンドキュー取得関数
/// </summary>
/// <returns>コマンドキュー参照</returns>
[[nodiscard]] ID3D12CommandQueue* CommandQueue::get_command_queue() const noexcept {
	assert(command_queue && "コマンドキュー nulptr");
	return command_queue.Get();
}