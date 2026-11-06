#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../TransformBuffer.h"
#include"DescriptorGroupBase.h"

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

			class TransformBufferGroup : public DesctirptorGroupBase<TransformBuffer>
			{
				using Transform = HandyItems::Math::Transform;
			public:

				/* ===== 初期化関数 ===== */

				[[nodiscard]] HRESULT create_constant_buffer_group(
					ID3D12Device* device_,
					DescriptorHeapAllocator* allocator,
					const CurrentIndexBase* index,
					const Transform& data
				) {
					//	DesctirptorGroupBase初期化
					{
						const auto hr = initialize_resource_group(allocator, index);
						if (FAILED(hr)) {
							return hr;
						}
					}

					//	TransformBuffer初期化
					{
						for (std::size_t i = 0; i < group_instances.size(); i++) {

							auto& instance = group_instances[i];

							instance = std::make_unique<TransformBuffer>();

							auto handles = get_handles(i);
							if (!handles.has_value()) {
								return E_OUTOFMEMORY;
							}

							const auto hr = instance->create_transform_buffer(
								device_,
								handles.value()
							);
							if (FAILED(hr)) {
								return hr;
							}

							instance->update_buffer(data);
						}
					}
					return S_OK;
				}

				bool update_buffer(const Transform& data) {
					return get_current_instance()->update_buffer(data);
				}

			};
		}
	}
}