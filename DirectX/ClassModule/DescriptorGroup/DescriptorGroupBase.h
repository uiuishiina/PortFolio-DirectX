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

				explicit DesctirptorGroupBase(
					State::HeapState state
				) :
					DescriptorResource{ state } {}

				virtual ~DesctirptorGroupBase() = default;

				[[nodiscard]] HRESULT initialize_resource_group(
					DescriptorHeapAllocator* allocator
				) {
					const auto hr = initialize_resource(allocator);
					if (FAILED(hr)) {
						return hr;
					}

					const auto size = get_handles_vec_size();

					current_index = std::make_unique<HandyItems::others::CircularIndex>(
						size
					);
					group_instances.resize(size);
					return hr;
				}

				void update_index() {
					if (!current_index) {
						return;
					}

					auto index = current_index.get();
					++*index;
				}

				[[nodiscard]] std::size_t get_current_index() const noexcept {
					return *current_index.get();
				}

				[[nodiscard]] T* get_current_instance() const noexcept {
					if (!current_index) {
						return nullptr;
					}
					
					auto size = *current_index.get();
					return group_instances[size].get();
				}

				[[nodiscard]] std::optional<Helper::DescriptorHeapHandles> get_current_handles() const noexcept {
					if (!current_index) {
						return std::nullopt;
					}
					return get_handles(*current_index.get());
				}

				[[nodiscard]] T* get_instance(std::size_t index) const noexcept {
					if (index >= group_instances.size()) {
						return nullptr;
					}
					return group_instances[index].get();
				}

			protected:

				std::unique_ptr<HandyItems::others::CircularIndex> current_index{};

				std::vector<std::unique_ptr<T>> group_instances{};
			};

		}
	}
}