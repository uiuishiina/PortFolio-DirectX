#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../../ClassObject/GPUResource/DepthBuffer.h"
#include"DescriptorGroupBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {


		namespace DescriptorGroup {


			class DepthBufferGroup final : public DesctirptorGroupBase<ClassObject::DepthBuffer>
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/* ===== 初期化関数 ===== */

				/// <summary>
				/// デプスバッファグループ作成関数
				/// </summary>
				/// <param name="device_">Device参照</param>
				/// <param name="allocator">[DSV] ディスクリプターヒープアロケータ参照</param>
				/// <param name="desc">デプスバッファ設定構造体</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_depth_buffer_group(
					ID3D12Device* device_,
					DescriptorHeapAllocator* allocator,
					const CurrentIndexBase* index,
					ClassObject::desc::DepthBufferDesc desc
				) {

					//	DescriptorResource初期化
					{
						const auto hr = initialize_resource_group(allocator, index);
						if (FAILED(hr)) {
							return hr;
						}
					}

					//	DepthBuffer初期化
					{
						
						for (std::size_t i = 0; i < group_instances.size(); i++) {

							group_instances[i] = std::make_unique<ClassObject::DepthBuffer>();

							auto handles = get_handles(i);
							if (!handles.has_value()) {
								return E_OUTOFMEMORY;
							}

							const auto hr = group_instances[i]->creata_depth_buffer(
								device_,
								handles->cpu_handle,
								desc
							);
							if (FAILED(hr)) {
								return hr;
							}
						}
					}
					return S_OK;
				}

			};
		}
	}
}