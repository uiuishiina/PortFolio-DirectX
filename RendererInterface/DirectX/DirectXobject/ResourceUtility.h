#pragma once
#include<d3d12.h>
#include<wrl/client.h>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DirectXオブジェクト補助名前空間
		/// </summary>
		namespace utility {

			/// <summary>
			/// リソース作成補助ディスクリプタヒープハンドル構造体
			/// </summary>
			/// <details>
			/// CPUハンドルとGPUハンドルを同時取得できるようにするための構造体
			/// </details>
			struct Descripter_Handles {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// CPUハンドル
				/// </summary>
				D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle{};

				/// <summary>
				/// GPUハンドル
				/// </summary>
				D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle{};


				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				Descripter_Handles() = default;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="CPU">CPUハンドル</param>
				/// <param name="GPU">GPUハンドル</param>
				Descripter_Handles(
					D3D12_CPU_DESCRIPTOR_HANDLE CPU, 
					D3D12_GPU_DESCRIPTOR_HANDLE GPU
				) :cpu_handle{ CPU }, gpu_handle{ GPU } {}

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="heap">ディスクリプタヒープ参照</param>
				/// <param name="type">ディスクリプタヒープタイプ</param>
				/// <param name="index">オフセットインデックス</param>
				Descripter_Handles(
					ID3D12Device* device, 
					ID3D12DescriptorHeap* heap, 
					D3D12_DESCRIPTOR_HEAP_TYPE type, 
					UINT index
				) {

					const auto offset = device->GetDescriptorHandleIncrementSize(type) * index;

					cpu_handle = heap->GetCPUDescriptorHandleForHeapStart();
					cpu_handle.ptr += offset;

					gpu_handle = heap->GetGPUDescriptorHandleForHeapStart();
					gpu_handle.ptr += offset;
				}

			};
		}
	}
}