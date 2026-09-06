#include"CommandObjectFactory.h"
#include"../DirectXobject/Device.h"

using namespace render::dx12::factory;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// 描画用コマンドキュー作成関数
/// </summary>
/// <param name="device"></param>
/// <param name="out">受け渡すインスタンス参照</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT CommandObjectFactory::create_graphics_command_queue(
	ID3D12Device* device, 
	object::CommandQueue& out
) {
	return out.create_command_queue(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
}

/// <summary>
/// 描画用コマンドアロケーター作成関数
/// </summary>
/// <param name="device"></param>
/// <param name="out">受け渡すインスタンス</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT CommandObjectFactory::create_graphics_command_allocator(
	ID3D12Device* device, 
	object::CommandAllocator& out
) {
	return out.create_command_allocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
}

/// <summary>
/// 描画用コマンドリスト作成関数
/// </summary>
/// <param name="device">DirectX12デバイスポインター</param>
/// <param name="allocator">作成に利用する描画用アロケーター</param>
/// <param name="out">受け渡すインスタンス</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT CommandObjectFactory::create_graphics_command_list(
	ID3D12Device* device, 
	ID3D12CommandAllocator* allocator, 
	object::GraphicsCommandList& out
) {
	return out.create_graphics_command_list(device, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator);
}