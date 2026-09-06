#pragma once
#include"Others/NonCopyableBase.h"
#include<dxgi1_6.h>
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
			/// GPUリソース設定構造体
			/// </summary>
			struct ResourceCreateDesc {

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
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// GPUリソース基底クラス
			/// </summary>
			class GPUResourceBase : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				GPUResourceBase() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~GPUResourceBase() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// リソース取得関数
				/// </summary>
				/// <returns>リソース参照</returns>
				[[nodiscard]] ID3D12Resource* get_resource()const noexcept;

			protected:
				/* ========== Protectedメンバー変数 ========== */

				/// <summary>
				/// リソースインスタンス
				/// </summary>
				Microsoft::WRL::ComPtr<ID3D12Resource> resource_{};


				/* ========== Protectedメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// リソース作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="desc">GPUリソース設定構造体</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_committed_resource(
					ID3D12Device* device, 
					const desc::ResourceCreateDesc& desc
				);

				/// <summary>
				/// リソース作成関数 
				/// </summary>
				/// <details>
				/// 追加でリソースが必要な場合に [メンバー変数以外] のリソースを作成できる関数
				/// </details>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="desc">GPUリソース設定構造体</param>
				/// <param name="resource">作成するリソース先参照</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_committed_resource(
					ID3D12Device* device, 
					const desc::ResourceCreateDesc& desc, 
					Microsoft::WRL::ComPtr<ID3D12Resource>& resource
				);

				/* -- 取得関数 -- */

				/// <summary>
				/// リソース設定取得関数
				/// </summary>
				/// <returns>リソース設定</returns>
				[[nodiscard]] D3D12_RESOURCE_DESC get_desc() const noexcept;

				/// <summary>
				/// GPUアドレス取得関数
				/// </summary>
				/// <returns>GPUアドレス</returns>
				[[nodiscard]] D3D12_GPU_VIRTUAL_ADDRESS get_GPU_address() const noexcept;

			};
		}
	}
}