#include"StaticHeapContainer.h"
#include<cassert>

using namespace render::dx12::container;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== ディスクリプタヒープコンテナ作成関数 ===
//@param	device	DirectX12 デバイス
//@param	desc	ディスクリプタヒープ設定配列
//@return	作成の可否
[[nodiscard]] HRESULT StaticHeapContainer::create_static_heap_container(ID3D12Device* device, const std::vector<desc::DescriptorHeapDesc>& desc) {

	//	空ならエラーを返す
	if (desc.empty()) {
		return E_FAIL;
	}

	
	//	設定分作成
	for (auto& value : desc) {
		
		auto [type, num, flag] = value;

		//	既に作成されているならエラーを返す
		const auto it = static_heap_map.find(type);
		if (it != static_heap_map.end()) {
			return E_FAIL;
		}

		auto heap = std::make_unique<object::DescriptorHeap>();

		const auto hr = heap->create_descriptor_heap(device, type, num, flag);
		if (FAILED(hr)) {
			return hr;
		}

		static_heap_map.emplace(type, std::move(heap));
	}

	return S_OK;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== ディスクリプタヒープ参照取得関数 ===
//@param	type	ディスクリプターヒープタイプ
//@return	ディスクリプターヒープポインター
[[nodiscard]] render::dx12::object::DescriptorHeap* StaticHeapContainer::get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE type) {

	//	マップ探索
	auto it = static_heap_map.find(type);
	if (it == static_heap_map.end()) {
		return nullptr;
	}
	return it->second.get();
}