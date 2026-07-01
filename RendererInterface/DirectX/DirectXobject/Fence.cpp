#include"Fence.h"

#include<cassert>

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== フェンス作成関数 ===
//@param	device	DirectX12 デバイス
//@return	作成の成否
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

	return S_OK;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	コマンドキューにフェンスをシグナル
//@param	command_queue	フェンスをシグナルするコマンドキュー
[[nodiscard]] UINT64 Fence::signal(ID3D12CommandQueue* command_queue) {

	assert(fence_ && "フェンス nullptr");
	fence_value++;
	const auto hr = command_queue->Signal(fence_.Get(), fence_value);
	assert(SUCCEEDED(hr) && "signal FAILED");
	return fence_value;
}

//@brief	フェンスの値を待機
//@param	completed_value	待機するフェンスの値
void Fence::wait_to_completed_value(UINT64 completed_value) const noexcept {

	assert(fence_ && "フェンス nullptr");
	const auto hr = fence_->SetEventOnCompletion(completed_value, wait_event);
	assert(SUCCEEDED(hr) && "wait_to_completed_value FAILED");
	WaitForSingleObject(wait_event, INFINITE);
}

//@brief	フェンス値の取得
//@return	フェンス値
[[nodiscard]] UINT64 Fence::get_completed_value() const noexcept {
	assert(fence_ && "フェンス nullptr");
	return fence_->GetCompletedValue();
}

//@brief	=== フェンス取得関数 ===
//@return	フェンスインスタンス
[[nodiscard]] ID3D12Fence* Fence::get_fence()const noexcept {
	assert(fence_ && "フェンス nullptr");
	return fence_.Get();
}