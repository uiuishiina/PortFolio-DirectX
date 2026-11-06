#pragma once

/* ========== Includeファイル ========== */

#include"Others/CircularIndex.h"

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
			class DesctirptorGroupBase : protected DescriptorResource
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				virtual ~DesctirptorGroupBase() = default;

				[[nodiscard]] HRESULT initialize_resource_group(
					DescriptorHeapAllocator* allocator,
					const CurrentIndexBase* index
				) {
					current_index = index;

					const auto hr = initialize_resource(
						allocator, 
						current_index
					);
					if (FAILED(hr)) {
						return hr;
					}

					const auto size = get_handles_vec_size();
					group_instances.resize(size);

					return hr;
				}

				[[nodiscard]] T* get_current_instance() const noexcept {

					return group_instances[current_index->get_current_index()].get();
				}

				[[nodiscard]] std::optional<Helper::DescriptorHeapHandles> get_current_handles() const noexcept {
					
					return get_handles(current_index->get_current_index());
				}

				[[nodiscard]] T* get_instance(std::size_t index) const noexcept {
					if (index >= group_instances.size()) {
						return nullptr;
					}
					return group_instances[index].get();
				}

			protected:

				const CurrentIndexBase* current_index{};

				std::vector<std::unique_ptr<T>> group_instances{};
			};

		}
	}
}