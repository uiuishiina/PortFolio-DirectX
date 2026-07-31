#pragma once
#include<d3d12.h>
#include<wrl/client.h>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// DirectXオブジェクト補助名前空間
		///====================================================================

		namespace utility {

			//@brief	=== リソース作成補助ディスクリプタヒープハンドル構造体 ===
			struct Descripter_Handles
			{
				//@brief	== CPUハンドル ==
				D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle{};

				//@brief	== GPUハンドル ==
				D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle{};

				//コンストラクタ
				Descripter_Handles() = default;

				//@brief	=== 引数付きコンストラクタ ===
				//@param	device	DirectX12 Device
				//@param	heap	ディスクリプタヒープ参照
				//@param	type	ディスクリプタヒープタイプ
				//@param	index	オフセットインデックス
				Descripter_Handles(ID3D12Device* device, ID3D12DescriptorHeap* heap, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT index) {

					const auto offset = device->GetDescriptorHandleIncrementSize(type) * index;

					cpu_handle = heap->GetCPUDescriptorHandleForHeapStart();
					cpu_handle.ptr += offset;

					gpu_handle = heap->GetGPUDescriptorHandleForHeapStart();
					gpu_handle.ptr += offset;
				};
			};
		};
	};
};