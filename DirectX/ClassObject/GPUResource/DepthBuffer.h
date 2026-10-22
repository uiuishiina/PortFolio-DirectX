#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"GPUResourceBase.h"
#include"../DescriptorResource.h"

#include"../../Helpers/GPUResourceHelper.h"
#include"../../Helpers/GPUResourceDescHelper.h"



/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// DirectXオブジェクト設定構造体名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// デプスバッファ設定構造体
			/// </summary>
			struct DepthBufferDesc {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// バッファの横幅
				/// </summary>
				UINT64 width = 1;

				/// <summary>
				/// バッファの縦幅
				/// </summary>
				UINT height = 1;

				/// <summary>
				/// バッファのフォーマット
				/// </summary>
				DXGI_FORMAT format = DXGI_FORMAT_D32_FLOAT;

				/// <summary>
				/// ピクセルごとのサンプル数
				/// </summary>
				UINT sample_count = 1;

				/// <summary>
				/// クリア時のデプス値
				/// </summary>
				float clear_depth = 1.0f;

				/// <summary>
				/// クリア時のステンシル値
				/// </summary>
				UINT8 clear_stencil = 0;

			};
		}

		/// <summary>
		/// デプスバッファクラス
		/// </summary>
		class DepthBuffer final : public GPUResourceBase,protected DescriptorResource
		{
		public:
			/* ========== Publicメンバー関数 ========== */
			
			/// <summary>
			/// コンストラクタ
			/// </summary>
			DepthBuffer() :
				GPUResourceBase(),
				DescriptorResource(State::HeapState::Static) {}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DepthBuffer() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// デプスバッファ作成関数
			/// </summary>
			/// <param name="device">Device参照</param>
			/// <param name="handle">DSVディスクリプタヒープハンドル</param>
			/// <param name="desc">デプスバッファ設定構造体参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT creata_depth_buffer(
				ID3D12Device* device,
				DescriptorHeapAllocator* allocator,
				desc::DepthBufferDesc desc
			) {

				
				{
					const auto hr = initialize_resource(allocator);
					if (FAILED(hr)) {
						return hr;
					}
				}

				//	リソース設定
				desc::GPUResourceDesc resource_desc{};

				resource_desc.heap_properties = Helper::GPUResourceDescHelper::get_heap_properties(
					D3D12_HEAP_TYPE_DEFAULT
				);

				resource_desc.heap_flags = D3D12_HEAP_FLAG_NONE;

				resource_desc.resource_desc = Helper::GPUResourceDescHelper::get_tex2D_desc(
					desc.format, 
					desc.width, 
					desc.height, 
					1, 
					1, 
					desc.sample_count, 
					0, 
					D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
				);

				resource_desc.initial_state = D3D12_RESOURCE_STATE_DEPTH_WRITE;

				//	クリア値設定
				D3D12_CLEAR_VALUE clearValue{};
				clearValue.Format = desc.format;
				clearValue.DepthStencil.Depth = desc.clear_depth;
				clearValue.DepthStencil.Stencil = desc.clear_stencil;

				resource_desc.clear_value = &clearValue;

				//	リソース作成
				const auto hr = create_committed_resource(device, resource_desc);
				if (FAILED(hr)) {
					return hr;
				}

				//	DSV作成
				D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
				dsvDesc.Format = desc.format;
				dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
				dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

				
				device->CreateDepthStencilView(resource_.Get(), &dsvDesc, get_handles_vec()[0].cpu_handle);

				return hr;
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// DSVハンドル取得関数
			/// </summary>
			/// <returns>DSV CPUハンドル</returns>
			[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_DSV_handle() const noexcept {

				return get_handles_vec()[0].cpu_handle;
			}

		};
	}
}