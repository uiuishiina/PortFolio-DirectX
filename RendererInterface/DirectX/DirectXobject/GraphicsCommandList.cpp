#include"GraphicsCommandList.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== コマンドリスト作成関数 ===
//@param	device	DirectX12 デバイス
//@param	type	コマンドリストタイプ
//@param	allocator	コマンドアロケータ参照
//@return	作成の成否
[[nodiscard]] HRESULT GraphicsCommandList::create_graphics_command_list(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type,
	ID3D12CommandAllocator* allocator) {

	const auto hr = device->CreateCommandList(
		0,						//	ノードマスク
		type,					//	コマンドリストのタイプ
		allocator,				//	コマンドアロケータ
		nullptr,				//	初期パイプラインステート（必要に応じて指定）
		IID_PPV_ARGS(&command_list_) // コマンドリストの取得
	);
	if (FAILED(hr)) {
		return hr;
	}

	command_list_->Close(); // コマンドリストは作成後にクローズする必要がある
	return hr;
}

///====================================================================
/// 実行時処理関数
///====================================================================
 
//@brief	=== 描画用コマンドリストリセット関数 ===
//@param	allocator	コマンドリストをリセットするコマンドアロケータ参照
void GraphicsCommandList::reset_command_list(ID3D12CommandAllocator* allocator) {

	assert(command_list_ && "コマンドリスト nullptr");
	const auto hr = command_list_->Reset(allocator, nullptr);
	assert(SUCCEEDED(hr) && "reset_command_list FAILED");
}

//@brief	=== コマンドリスト取得関数 ===
//@return	コマンドリスト参照
[[nodiscard]] ID3D12GraphicsCommandList* GraphicsCommandList::get_graphics_command_list() const noexcept {
	assert(command_list_ && "コマンドリスト nullptr");
	return command_list_.Get();
}