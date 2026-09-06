#include"Fence.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// フェンス作成関数
/// </summary>
/// <param name="device">DirectX12デバイス参照</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT Fence::create_fence(ID3D12Device* device) {

	const auto hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	if (FAILED(hr)) {
		return hr;
	}

	//	フェンスイベントの作成
	wait_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (!wait_event) {
		return E_FAIL;
	}

	return hr;
}

/* -- フェンス利用関数 -- */

/// <summary>
/// フェンスシグナル関数
/// </summary>
/// <param name="command_queue">シグナルするコマンドキュー参照</param>
/// <returns>シグナルした値</returns>
[[nodiscard]] const UINT64 Fence::signal(ID3D12CommandQueue* command_queue) {

	assert(fence_ && "フェンス nullptr");
	fence_value++;
	const auto hr = command_queue->Signal(fence_.Get(), fence_value);
	assert(SUCCEEDED(hr) && "signal FAILED");
	return fence_value;
}

/// <summary>
/// フェンス待機関数
/// </summary>
/// <param name="completed_value">待機するフェンスの値</param>
void Fence::wait_to_completed_value(UINT64 completed_value) const noexcept {

	assert(fence_ && "フェンス nullptr");
	const auto hr = fence_->SetEventOnCompletion(completed_value, wait_event);
	assert(SUCCEEDED(hr) && "wait_to_completed_value FAILED");
	WaitForSingleObject(wait_event, INFINITE);
}


/* -- 取得関数 -- */

/// <summary>
/// フェンス値取得関数
/// </summary>
/// <returns>動作完了したフェンス値</returns>
[[nodiscard]] const UINT64 Fence::get_completed_value() const noexcept {
	assert(fence_ && "フェンス nullptr");
	return fence_->GetCompletedValue();
}

/// <summary>
/// 現在シグナル値取得関数
/// </summary>
/// <returns>フェンスの値</returns>
[[nodiscard]] const UINT64 Fence::get_now_signal_value()const noexcept {
	return fence_value;
}

/// <summary>
/// フェンス取得関数
/// </summary>
/// <returns>フェンス参照</returns>
[[nodiscard]] ID3D12Fence* Fence::get_fence()const noexcept {
	assert(fence_ && "フェンス nullptr");
	return fence_.Get();
}