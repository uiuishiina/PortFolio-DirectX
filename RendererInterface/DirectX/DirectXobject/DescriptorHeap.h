#pragma once
#include"Others/NonCopyableBase.h"
#include"ResourceUtility.h"
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
		/// DX12オブジェクト設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// ディスクリプタヒープ作成補助構造体
			/// </summary>
			struct DescriptorHeapDesc {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// ディスクリプターヒープタイプ設定
				/// </summary>
				D3D12_DESCRIPTOR_HEAP_TYPE type_;

				/// <summary>
				/// ディスクリプターヒープサイズ設定
				/// </summary>
				UINT numDescriptors_;

				/// <summary>
				/// シェーダー可視設定
				/// </summary>
				D3D12_DESCRIPTOR_HEAP_FLAGS flags_;


				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DescriptorHeapDesc() = default;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="type">ディスクリプターヒープタイプ設定</param>
				/// <param name="size">ディスクリプターヒープサイズ設定</param>
				/// <param name="flags">シェーダー可視設定</param>
				DescriptorHeapDesc(
					D3D12_DESCRIPTOR_HEAP_TYPE type,
					UINT size,
					D3D12_DESCRIPTOR_HEAP_FLAGS flags
				) :type_{ type }, numDescriptors_{ size }, flags_{ flags } {}

			};
		}

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// ディスクリプタヒープクラス
			/// </summary>
			class DescriptorHeap final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DescriptorHeap() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~DescriptorHeap() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// ディスクリプタヒープ作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="desc">ディスクリプタヒープ作成補助構造体参照</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_descriptor_heap(
					ID3D12Device* device, 
					const desc::DescriptorHeapDesc& desc
				);

				/* -- 取得関数 -- */

				/// <summary>
				/// ディスクリプタヒープ取得関数
				/// </summary>
				/// <returns>ディスクリプタヒープ参照</returns>
				[[nodiscard]] ID3D12DescriptorHeap* get_descriptor_heap() const noexcept;

				/// <summary>
				/// CPU ディスクリプタハンドル取得関数
				/// </summary>
				/// <param name="index">ディスクリプタインデックス</param>
				/// <returns>CPU ディスクリプタハンドル</returns>
				[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_cpu_descriptor_handle(UINT index) const noexcept;

				/// <summary>
				/// GPU ディスクリプタハンドル取得関数
				/// </summary>
				/// <param name="index">ディスクリプタインデックス</param>
				/// <returns>GPU ディスクリプタハンドル</returns>
				[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE get_gpu_descriptor_handle(UINT index) const noexcept;

				/// <summary>
				/// ディスクリプタヒープハンドルズ構造体取得関数
				/// </summary>
				/// <param name="index">ディスクリプタインデックス</param>
				/// <returns>ディスクリプタヒープハンドルズ構造体</returns>
				[[nodiscard]] utility::Descripter_Handles get_descriptor_handles(UINT index) const noexcept;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// ディスクリプタヒープメモリサイズ
				/// </summary>
				UINT descriptor_size{};

				/// <summary>
				/// ディスクリプタヒープインスタンス
				/// </summary>
				Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_{};

			};
		}
	}
}