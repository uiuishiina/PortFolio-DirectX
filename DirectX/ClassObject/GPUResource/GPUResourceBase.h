#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include<d3d12.h>
#include<wrl/client.h>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト設定構造体名前空間
	/// </summary>
	namespace desc {

		/// <summary>
		/// GPUリソース設定構造体
		/// </summary>
		struct GPUResourceDesc {

			/* ========== メンバー変数 ========== */

			/// <summary>
			/// ヒーププロパティ設定
			/// </summary>
			D3D12_HEAP_PROPERTIES heap_properties{};

			/// <summary>
			/// ヒープフラグ設定
			/// </summary>
			D3D12_HEAP_FLAGS heap_flags = D3D12_HEAP_FLAG_NONE;

			/// <summary>
			/// リソース設定
			/// </summary>
			D3D12_RESOURCE_DESC resource_desc{};

			/// <summary>
			/// 初期リソースステート
			/// </summary>
			D3D12_RESOURCE_STATES initial_state = D3D12_RESOURCE_STATE_COMMON;

			/// <summary>
			/// クリア値設定
			/// </summary>
			const D3D12_CLEAR_VALUE* clear_value = nullptr;

		};
	}

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// GPUリソース基底クラス
		/// </summary>
		class GPUResourceBase : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 取得関数 ===== */

			/// <summary>
			/// リソース参照取得関数
			/// </summary>
			/// <returns>リソース参照</returns>
			[[nodiscard]] ID3D12Resource* get()const noexcept {

				return resource_.Get();
			}

			/// <summary>
			/// リソース参照アロー演算子オーバーロード
			/// </summary>
			/// <returns>リソース参照</returns>
			[[nodiscard]] ID3D12Resource* operator -> () const noexcept {

				return get();
			}

		protected:
			/* ========== Protectedメンバー変数 ========== */

			/// <summary>
			/// リソースインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<ID3D12Resource> resource_{};

			/* ========== Protectedメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			GPUResourceBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~GPUResourceBase() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// GPUリソース作成関数
			/// </summary>
			/// <param name="device">Device参照</param>
			/// <param name="desc">GPUリソース設定構造体</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_committed_resource(
				ID3D12Device* device_,
				const desc::GPUResourceDesc& desc
			) {

				const auto hr = device_->CreateCommittedResource(
					&desc.heap_properties,
					desc.heap_flags,
					&desc.resource_desc,
					desc.initial_state,
					desc.clear_value,
					IID_PPV_ARGS(resource_.ReleaseAndGetAddressOf()));
				return hr;
			}

			/// <summary>
			/// リソース作成関数 
			/// </summary>
			/// <details>
			/// 追加でリソースが必要な場合に [メンバー変数以外] のリソースを作成できる関数
			/// </details>
			/// <param name="device">Device参照</param>
			/// <param name="desc">GPUリソース設定構造体</param>
			/// <param name="resource">作成するリソース先参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_committed_resource(
				ID3D12Device* device,
				const desc::GPUResourceDesc& desc,
				Microsoft::WRL::ComPtr<ID3D12Resource>& resource
			) {

				return device->CreateCommittedResource(
					&desc.heap_properties,
					desc.heap_flags,
					&desc.resource_desc,
					desc.initial_state,
					desc.clear_value,
					IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// リソース設定取得関数
			/// </summary>
			/// <returns>リソース設定</returns>
			[[nodiscard]] D3D12_RESOURCE_DESC get_desc() const noexcept {

				return resource_->GetDesc();
			}

			/// <summary>
			/// GPUアドレス取得関数
			/// </summary>
			/// <returns>GPUアドレス</returns>
			[[nodiscard]] D3D12_GPU_VIRTUAL_ADDRESS get_GPU_address() const noexcept {

				return resource_->GetGPUVirtualAddress();
			}

		};
	}
}