#include"GraphicsCommandList.h"

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== コマンドリスト作成関数 ===
//@param	device	DirectX12 デバイス
//@param	type	コマンドリストタイプ
//@param	allocator	コマンドアロケータインスタンス
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
	return S_OK;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== コマンドリスト取得関数 ===
//@return	コマンドリストインスタンス
[[nodiscard]] ID3D12GraphicsCommandList* GraphicsCommandList::get_graphics_command_list() const noexcept {
	return command_list_.Get();
}