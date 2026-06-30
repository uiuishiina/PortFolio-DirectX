#include"CommandAllocator.h"

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== コマンドアロケータ作成関数 ===
//@param	device	DirectX12 デバイス
//@param	type	コマンドリストタイプ
//@return	作成の成否
[[nodiscard]] HRESULT CommandAllocator::create_command_allocator(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type) {

	return device->CreateCommandAllocator(type, IID_PPV_ARGS(&command_allocator_));
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== コマンドアロケータ取得関数 ===
//@return	コマンドアロケータインスタンス
[[nodiscard]] ID3D12CommandAllocator* CommandAllocator::get_command_allocator() const noexcept {
	return command_allocator_.Get();
}