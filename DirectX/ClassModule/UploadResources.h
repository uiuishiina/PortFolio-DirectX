#pragma once


/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include"Container/ReferenceQueue.h"

#include<d3d12.h>
#include<wrl/client.h>

#include<vector>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {


		class UploadResources final : HandyItems::others::NonCopyableBase
		{
		public:

			UploadResources() = delete;

			UploadResources(
				std::size_t size
			) :
				upload_{ upload_ = std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>(size) }
			{
				reference_.add_references(upload_);
			}


			~UploadResources() = default;

			[[nodiscard]] ID3D12Resource* allocate_reference() {

				if (auto value = reference_.get_reference();
					value.has_value()
					) {
					return value->get().Get();
				}

				return nullptr;
			}

			[[nodiscard]] std::vector<ID3D12Resource*> allocate_references(
				std::size_t size
			) {
				
				std::vector<ID3D12Resource*> vec{};

				for (std::size_t i = 0; i < size; i++) {
					vec.push_back(allocate_reference());
				}

				return vec;
			}

			void clear() {
				reference_.clear();
				upload_.clear();
			}

		private:

			std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> upload_{};

			HandyItems::container::ReferenceQueue<Microsoft::WRL::ComPtr<ID3D12Resource>> reference_{};
		};
	}
}