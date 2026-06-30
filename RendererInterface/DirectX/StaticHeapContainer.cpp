#include"StaticHeapContainer.h"

//@brief	=== ディスクリプタヒープコンテナ作成関数 ===
//@param	device	DirectX12 デバイス
//@param	desc	ディスクリプタヒープ設定配列
//@return	作成の可否
[[nodiscard]] HRESULT StaticHeapContainer::create_static_heap_container(ID3D12Device* device, const std::vector<DescriptorHeapDesc>& desc) {

	//	空ならエラーを返す
	if (desc.empty()) {
		return E_FAIL;
	}

	//	設定分作成
	for (auto& value : desc) {
		auto heap = std::make_unique<DescriptorHeap>();

		auto [type, num, flag] = value;
		const auto hr = heap->create_descriptor_heap(device, type, num, flag);
		if (FAILED(hr)) {
			return hr;
		}

		static_heap_map.emplace(type, std::move(heap));
	}

	return S_OK;
}