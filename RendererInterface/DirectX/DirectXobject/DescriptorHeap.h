#pragma once
#include"NonMovable.h"
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
		/// DX12オブジェクトラッパークラス名前空間
		///====================================================================

		namespace object {

			///====================================================================
			/// DescriptorHeap クラス
			///====================================================================

			//@brief	=== ディスクリプタヒープクラス ===
			class DescriptorHeap final : public NonMovableBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				DescriptorHeap() = default;
				~DescriptorHeap() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== ディスクリプタヒープ作成関数 ===
				//@param	device			DirectX12 デバイス
				//@param	type			ディスクリプタヒープタイプ
				//@param	num_descriptors	ディスクリプタ数
				//@param	flags			ディスクリプタヒープフラグ
				//@return	作成の成否
				[[nodiscard]] HRESULT create_descriptor_heap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type,
					UINT num_descriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flags);

				//@brief	=== ディスクリプタヒープ取得関数 ===
				//@return	ディスクリプタヒープインスタンス
				[[nodiscard]] ID3D12DescriptorHeap* get_descriptor_heap() const noexcept;

				//@brief	=== CPU ディスクリプタハンドル取得関数 ===
				//@param	index	ディスクリプタインデックス
				//@return	CPU ディスクリプタハンドル
				[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_cpu_descriptor_handle(UINT index) const noexcept;

				//@brief	=== GPU ディスクリプタハンドル取得関数 ===
				//@param	index	ディスクリプタインデックス
				//@return	GPU ディスクリプタハンドル
				[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE get_gpu_descriptor_handle(UINT index) const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== ディスクリプタヒープメモリサイズ ==
				UINT descriptor_size_{};

				//@brief	== ディスクリプタヒープインスタンス ==
				Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_{};

			};
		};
	};
};