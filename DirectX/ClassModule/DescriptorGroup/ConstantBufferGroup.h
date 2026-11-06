#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../../ClassObject/GPUResource/ConstantBuffer.h"
#include"../DescriptorResource.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// ディスクリプターヒープグループ名前空間
		/// </summary>
		namespace DescriptorGroup {

			template<typename T>
			class ConstantBufferGroup : public DesctirptorGroupBase<ClassObject::ConstantBuffer<T>>
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/* ===== 初期化関数 ===== */

				/// <summary>
				/// コンスタントバッファグループ作成関数
				/// </summary>
				/// <param name="device_">Device参照</param>
				/// <param name="allocator">[CBV_SRV_UAV] ディスクリプターヒープアロケータ参照</param>
				/// <param name="data">コンスタントバッファに書き込むデータ</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_constant_buffer_group(
					ID3D12Device* device_,
					DescriptorHeapAllocator* allocator,
					const CurrentIndexBase* index,
					const T& data
				) {

					//	DescriptorResource初期化
					{
						const auto hr = this->initialize_resource_group(allocator, index);
						if (FAILED(hr)) {
							return hr;
						}
					}

					//	ConstantBuffer初期化
					{
						for (std::size_t i = 0; i < this->group_instances.size(); i++) {

							this->group_instances[i] = std::make_unique<ClassObject::ConstantBuffer<T>>();

							auto handles = this->get_handles(i);
							if (!handles.has_value()) {
								return E_OUTOFMEMORY;
							}

							const auto hr = this->group_instances[i]->create_constant_buffer(
								device_,
								handles.value(),
								data
							);
							if (FAILED(hr)) {
								return hr;
							}
						}
					}
					return S_OK;
				}

				bool update_buffer(const T& data) {
					return this->get_current_instance()->upload_buffer(data);
				}

			};
		}
	}
}