#pragma once
#include"NonMovable.h"
#include<dxgi1_6.h>
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
		/// DX12オブジェクト設定名前空間
		///====================================================================

		namespace desc {

			//@brief	=== GPUリソース設定構造体 ===
			struct ResourceCreateDesc
			{
				//@brief	== ヒーププロパティ設定 ==
				D3D12_HEAP_PROPERTIES heap_properties{};

				//@brief	== ヒープフラグ設定 ==
				D3D12_HEAP_FLAGS heap_flags = D3D12_HEAP_FLAG_NONE;

				//@brief	== リソース設定 ==
				D3D12_RESOURCE_DESC resource_desc{};

				//@brief	== 初期リソースステート ==
				D3D12_RESOURCE_STATES initial_state = D3D12_RESOURCE_STATE_COMMON;

				//@brief	== クリア値設定 ==
				const D3D12_CLEAR_VALUE* clear_value = nullptr;

			};
		};

		///====================================================================
		/// DX12オブジェクトラッパークラス名前空間
		///====================================================================

		namespace object {

			///====================================================================
			/// GPUResourceBase 基底クラス
			///====================================================================

			//@brief	=== GPUリソース基底クラス ===
			class GPUResourceBase : public NonMovableBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				GPUResourceBase() = default;
				virtual ~GPUResourceBase() = default;

				///====================================================================
				/// Public メンバー変数
				///====================================================================

				//@brief	=== リソース取得関数 ===
				//@return	リソース参照
				[[nodiscard]] ID3D12Resource* get_resource()const noexcept;

			protected:
				///====================================================================
				/// Protected メンバー変数
				///====================================================================

				//@brief	== リソースインスタンス ==
				Microsoft::WRL::ComPtr<ID3D12Resource> resource_{};

				///====================================================================
				/// protected メンバー関数
				///====================================================================

				//@brief	=== リソース作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	desc	GPUリソース設定構造体
				//@return	作成の成否
				[[nodiscard]] HRESULT create_committed_resource(ID3D12Device* device, const desc::ResourceCreateDesc& desc);

				//@brief	=== リソース作成オーバーロード関数 ===
				//@details	追加でリソースが必要な場合に [メンバー変数以外] のリソースを作成できる関数
				//@param	device		DirectX12 デバイス
				//@param	desc		GPUリソース設定構造体
				//@param	resource	作成するリソース先参照
				//@return	作成の成否
				[[nodiscard]] HRESULT create_committed_resource(ID3D12Device* device, const desc::ResourceCreateDesc& desc, Microsoft::WRL::ComPtr<ID3D12Resource>& resource);

				//@brief	=== リソース設定取得関数 ===
				//@return	リソース設定
				[[nodiscard]] D3D12_RESOURCE_DESC get_desc() const noexcept;

				//@brief	=== GPUアドレス取得関数 ===
				//@return	GPUアドレス
				[[nodiscard]] D3D12_GPU_VIRTUAL_ADDRESS get_GPU_address() const noexcept;

			};
		};
	};
};