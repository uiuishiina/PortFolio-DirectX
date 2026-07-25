#include"CommandAllocator.h"
#include<cassert>

using namespace render::dx12::object;

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

//@brief	=== コマンドアロケータリセット関数 ===
void CommandAllocator::reset_command_allocator() {

	assert(command_allocator_ && "コマンドアロケータ nullptr");
	const auto hr = command_allocator_->Reset();
	assert(SUCCEEDED(hr) && "reset_command_allocator FAILED");
}

//@brief	=== コマンドアロケータ取得関数 ===
//@return	コマンドアロケータインスタンス
[[nodiscard]] ID3D12CommandAllocator* CommandAllocator::get_command_allocator() const noexcept {
	assert(command_allocator_ && "コマンドアロケータ nullptr");
	return command_allocator_.Get();
}