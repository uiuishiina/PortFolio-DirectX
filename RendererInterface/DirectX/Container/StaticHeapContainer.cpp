#include"StaticHeapContainer.h"
#include<cassert>

using namespace render::dx12::container;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// ディスクリプタヒープコンテナ作成関数
/// </summary>
/// <param name="device">デバイスインスタンス</param>
/// <param name="desc">ディスクリプタヒープ設定配列</param>
/// <returns>作成の成否</returns>設定配列
[[nodiscard]] HRESULT StaticHeapContainer::create_static_heap_container(ID3D12Device* device, const std::vector<desc::DescriptorHeapDesc>& desc) {

	//	空ならエラーを返す
	if (desc.empty()) {
		return E_FAIL;
	}

	
	//	設定分作成
	for (auto& value : desc) {
		
		auto [type, num, flag] = value;
		auto heap = std::make_unique<object::DescriptorHeap>();

		const auto hr = heap->create_descriptor_heap(device, type, num, flag);
		if (FAILED(hr)) {
			return hr;
		}

		heap_map.add_value(type, std::move(heap));
	}

	return S_OK;
}


/* -- 取得関数 -- */

/// <summary>
/// ディスクリプタヒープ参照取得関数
/// </summary>
/// <param name="type">取得したいディスクリプタヒープタイプ</param>
/// <returns>ディスクリプタヒープ参照</returns>
[[nodiscard]] render::dx12::object::DescriptorHeap* StaticHeapContainer::get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE type) {

	//	マップ探索
	return heap_map.get_value_p(type)->get();
}