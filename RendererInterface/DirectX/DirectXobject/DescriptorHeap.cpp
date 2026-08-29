#include"DescriptorHeap.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== ディスクリプタヒープ作成関数 ===
//@param	device			DirectX12 デバイス
//@param	type			ディスクリプタヒープタイプ
//@param	num_descriptors	ディスクリプタ数
//@param	flags			ディスクリプタヒープフラグ
//@return	作成の成否
[[nodiscard]] HRESULT DescriptorHeap::create_descriptor_heap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type,
	UINT num_descriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flags) {

	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Type = type;
	desc.NumDescriptors = num_descriptors;
	desc.Flags = flags;

	//	ディスクリプタヒープを作成
	const auto hr = device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap_));
	if (FAILED(hr)) {
		return hr;
	}

	//	ディスクリプタヒープのメモリサイズを取得
	descriptor_size_ = device->GetDescriptorHandleIncrementSize(type);
	return hr;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== ディスクリプタヒープ取得関数 ===
//@return	ディスクリプタヒープ参照
[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap::get_descriptor_heap() const noexcept {
	assert(heap_ && "ディスクリプタヒープ nullptr");
	return heap_.Get();
}

//@brief	=== CPU ディスクリプタハンドル取得関数 ===
//@param	index	ディスクリプタインデックス
//@return	CPU ディスクリプタハンドル
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::get_cpu_descriptor_handle(UINT index) const noexcept {

	assert(heap_ && "ディスクリプタヒープ nullptr");
	D3D12_CPU_DESCRIPTOR_HANDLE handle{};
	handle.ptr = heap_.Get()->GetCPUDescriptorHandleForHeapStart().ptr + index * descriptor_size_;
	return handle;
}	

//@brief	=== GPU ディスクリプタハンドル取得関数 ===
//@param	index	ディスクリプタインデックス
//@return	GPU ディスクリプタハンドル
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::get_gpu_descriptor_handle(UINT index) const noexcept {

	assert(heap_ && "ディスクリプタヒープ nullptr");
	D3D12_GPU_DESCRIPTOR_HANDLE handle{};
	handle.ptr = heap_.Get()->GetGPUDescriptorHandleForHeapStart().ptr + index * descriptor_size_;
	return handle;
}

[[nodiscard]] render::dx12::utility::Descripter_Handles DescriptorHeap::get_descriptor_handles(UINT index) const noexcept {

	assert(heap_ && "ディスクリプタヒープ nullptr");
	D3D12_CPU_DESCRIPTOR_HANDLE cpu{};
	cpu.ptr = heap_.Get()->GetCPUDescriptorHandleForHeapStart().ptr + index * descriptor_size_;

	D3D12_GPU_DESCRIPTOR_HANDLE gpu{};
	gpu.ptr = heap_.Get()->GetGPUDescriptorHandleForHeapStart().ptr + index * descriptor_size_;

	return render::dx12::utility::Descripter_Handles(cpu, gpu);
}