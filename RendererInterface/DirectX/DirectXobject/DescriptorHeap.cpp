#include"DescriptorHeap.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// ディスクリプタヒープ作成関数
/// </summary>
/// <param name="device">DirectX12デバイス参照</param>
/// <param name="desc">ディスクリプタヒープ作成補助構造体参照</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT DescriptorHeap::create_descriptor_heap(
	ID3D12Device* device,
	const desc::DescriptorHeapDesc& desc
) {

	D3D12_DESCRIPTOR_HEAP_DESC desc_{};

	const auto [type, size, flag] = desc;

	desc_.Type = type;
	desc_.NumDescriptors = size;
	desc_.Flags = flag;

	//	ディスクリプタヒープを作成
	const auto hr = device->CreateDescriptorHeap(&desc_, IID_PPV_ARGS(&heap_));
	if (FAILED(hr)) {
		return hr;
	}

	//	ディスクリプタヒープのメモリサイズを取得
	descriptor_size = device->GetDescriptorHandleIncrementSize(type);
	return hr;
}


/* -- 取得関数 -- */

/// <summary>
/// ディスクリプタヒープ取得関数
/// </summary>
/// <returns>ディスクリプタヒープ参照</returns>
[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap::get_descriptor_heap() const noexcept {
	assert(heap_ && "ディスクリプタヒープ nullptr");
	return heap_.Get();
}

/// <summary>
/// CPU ディスクリプタハンドル取得関数
/// </summary>
/// <param name="index">ディスクリプタインデックス</param>
/// <returns>CPU ディスクリプタハンドル</returns>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::get_cpu_descriptor_handle(UINT index) const noexcept {

	assert(heap_ && "ディスクリプタヒープ nullptr");
	D3D12_CPU_DESCRIPTOR_HANDLE handle{};
	handle.ptr = heap_.Get()->GetCPUDescriptorHandleForHeapStart().ptr + index * descriptor_size;
	return handle;
}	

/// <summary>
/// GPU ディスクリプタハンドル取得関数
/// </summary>
/// <param name="index">ディスクリプタインデックス</param>
/// <returns>GPU ディスクリプタハンドル</returns>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::get_gpu_descriptor_handle(UINT index) const noexcept {

	assert(heap_ && "ディスクリプタヒープ nullptr");
	D3D12_GPU_DESCRIPTOR_HANDLE handle{};
	handle.ptr = heap_.Get()->GetGPUDescriptorHandleForHeapStart().ptr + index * descriptor_size;
	return handle;
}

/// <summary>
/// ディスクリプタヒープハンドルズ構造体取得関数
/// </summary>
/// <param name="index">ディスクリプタインデックス</param>
/// <returns>ディスクリプタヒープハンドルズ構造体</returns>
[[nodiscard]] render::dx12::utility::Descripter_Handles DescriptorHeap::get_descriptor_handles(UINT index) const noexcept {

	assert(heap_ && "ディスクリプタヒープ nullptr");
	D3D12_CPU_DESCRIPTOR_HANDLE cpu{};
	cpu.ptr = heap_.Get()->GetCPUDescriptorHandleForHeapStart().ptr + index * descriptor_size;

	D3D12_GPU_DESCRIPTOR_HANDLE gpu{};
	gpu.ptr = heap_.Get()->GetGPUDescriptorHandleForHeapStart().ptr + index * descriptor_size;

	return render::dx12::utility::Descripter_Handles(cpu, gpu);
}