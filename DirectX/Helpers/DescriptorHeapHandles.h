#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include<d3d12.h>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 補助名前空間
	/// </summary>
	namespace Helper {

		/// <summary>
		/// ディスクリプターハンドル補助構造体
		/// </summary>
		struct DescriptorHeapHandles {

			/* ========== Publicメンバー変数 ========== */

			/// <summary>
			/// CPUハンドル
			/// </summary>
			D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle{};

			/// <summary>
			/// GPUハンドル
			/// </summary>
			D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle{};

			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DescriptorHeapHandles() = default;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="cpu_hand"></param>
			/// <param name="gpu_hand"></param>
			DescriptorHeapHandles(
				D3D12_CPU_DESCRIPTOR_HANDLE cpu_hand,
				D3D12_GPU_DESCRIPTOR_HANDLE gpu_hand
			) :
				cpu_handle{ cpu_hand },
				gpu_handle{ gpu_hand } {}

		};
	}
}