#include"GraphicsCommandList.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// 描画用コマンドリスト作成関数
/// </summary>
/// <param name="device">DirectX12デバイス参照</param>
/// <param name="type">コマンドリストタイプ</param>
/// <param name="allocator">コマンドアロケータ参照</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT GraphicsCommandList::create_graphics_command_list(
	ID3D12Device* device, 
	D3D12_COMMAND_LIST_TYPE type,
	ID3D12CommandAllocator* allocator
) {

	//	描画用コマンドリスト作成
	const auto hr = device->CreateCommandList(
		0,						//	ノードマスク
		type,					//	コマンドリストのタイプ
		allocator,				//	コマンドアロケータ
		nullptr,				//	初期パイプラインステート（必要に応じて指定）
		IID_PPV_ARGS(&command_list) // コマンドリストの取得
	);
	if (FAILED(hr)) {
		return hr;
	}

	command_list->Close(); // コマンドリストは作成後にクローズする必要がある
	return hr;
}


/* -- リセット関数 -- */

/// <summary>
/// 描画用コマンドリストリセット関数
/// </summary>
/// <param name="allocator">コマンドリストをリセットするコマンドアロケータ参照</param>
void GraphicsCommandList::reset_command_list(ID3D12CommandAllocator* allocator) {

	assert(command_list && "コマンドリスト nullptr");
	const auto hr = command_list->Reset(allocator, nullptr);
	assert(SUCCEEDED(hr) && "reset_command_list FAILED");
}


/* -- 取得関数 -- */

/// <summary>
/// 描画用コマンドリスト取得関数
/// </summary>
/// <returns>コマンドリスト参照</returns>
[[nodiscard]] ID3D12GraphicsCommandList* GraphicsCommandList::get_graphics_command_list() const noexcept {
	assert(command_list && "コマンドリスト nullptr");
	return command_list.Get();
}