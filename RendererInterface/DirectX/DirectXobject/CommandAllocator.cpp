#include"CommandAllocator.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// コマンドアロケータ作成関数
/// </summary>
/// <param name="device">DirectX12デバイス参照</param>
/// <param name="type">コマンドリストタイプ</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT CommandAllocator::create_command_allocator(
	ID3D12Device* device, 
	D3D12_COMMAND_LIST_TYPE type
) {

	return device->CreateCommandAllocator(type, IID_PPV_ARGS(&command_allocator));
}

/* -- リセット関数 -- */

/// <summary>
/// コマンドアロケータリセット関数
/// </summary>
void CommandAllocator::reset_command_allocator() {

	assert(command_allocator && "コマンドアロケータ nullptr");
	const auto hr = command_allocator->Reset();
	assert(SUCCEEDED(hr) && "reset_command_allocator FAILED");
}

/* -- 取得関数 -- */

/// <summary>
/// コマンドアロケータ取得関数
/// </summary>
/// <returns>コマンドアロケータ参照</returns>
[[nodiscard]] ID3D12CommandAllocator* CommandAllocator::get_command_allocator() const noexcept {
	assert(command_allocator && "コマンドアロケータ nullptr");
	return command_allocator.Get();
}