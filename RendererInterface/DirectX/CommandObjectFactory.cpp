#include"CommandObjectFactory.h"
#include"DirectXobject/Device.h"


//@brief	=== 描画用コマンドキュー作成関数 ===
//@param	device	DirectX12 デバイス
//@param	outout	受け渡すインスタンス
//@return	作成の成否
[[nodiscard]] HRESULT CommandObjectFactory::create_graphics_command_queue(ID3D12Device* device, CommandQueue& out) {
	return out.create_command_queue(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
}

//@brief	=== 描画用コマンドアロケーター作成関数 ===
//@param	device	DirectX12 デバイス
//@param	outout	受け渡すインスタンス
//@return	作成の成否
[[nodiscard]] HRESULT CommandObjectFactory::create_graphics_command_allocator(ID3D12Device* device, CommandAllocator& out) {
	return out.create_command_allocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
}

//@brief	=== 描画用コマンドリスト作成関数 ===
//@param	device	DirectX12 デバイス
//@param	allocator	作成に利用する描画用アロケーター
//@param	outout	受け渡すインスタンス
//@return	作成の成否
[[nodiscard]] HRESULT CommandObjectFactory::create_graphics_command_list(ID3D12Device* device, ID3D12CommandAllocator* allocator, GraphicsCommandList& out) {
	return out.create_graphics_command_list(device, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator);
}