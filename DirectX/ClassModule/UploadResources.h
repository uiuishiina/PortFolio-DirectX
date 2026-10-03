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
			using Resource = Microsoft::WRL::ComPtr<ID3D12Resource>;
		public:

			UploadResources() = default;

			UploadResources(
				std::size_t size
			) {
				add_upload(size);
				reference_.add_references(upload_);
			}


			~UploadResources() = default;

			[[nodiscard]] std::reference_wrapper<Resource> allocate_reference() {

				if (auto value = reference_.get_reference();
					value.has_value()
					) {
					return value->get();
				}
				else {
					add_upload(1);
					return allocate_reference();
				}

			}

			[[nodiscard]] std::vector<std::reference_wrapper<Resource>> allocate_references(
				std::size_t size
			) {
				
				std::vector<std::reference_wrapper<Resource>> vec{};

				for (std::size_t i = 0; i < size; i++) {
					vec.push_back(allocate_reference());
				}

				return vec;
			}

			void add_upload(std::size_t size) {

				upload_.reserve(size);
				for (std::size_t i = 0;i < size;i++) {
					auto ins = Microsoft::WRL::ComPtr<ID3D12Resource>();
					upload_.emplace_back(ins);
					reference_.add_reference(upload_.back());
				}
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