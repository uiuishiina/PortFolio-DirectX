#include"Fence.h"

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

//@brief	コマンドキューにフェンスをシグナル
//@param	command_queue	フェンスをシグナルするコマンドキュー
[[nodiscard]] UINT64 Fence::signal(ID3D12CommandQueue* command_queue) {

	fence_value++;
	const auto hr = command_queue->Signal(fence_.Get(), fence_value);
	if (FAILED(hr)) {
		
	}
	return fence_value;
}

//@brief	フェンス値の取得
//@return	フェンス値
[[nodiscard]] UINT64 Fence::get_completed_value() const noexcept {
	return fence_->GetCompletedValue();
}

//@brief	=== フェンス取得関数 ===
//@return	フェンスインスタンス
[[nodiscard]] ID3D12Fence* Fence::get_fence()const noexcept {
	return fence_.Get();
}