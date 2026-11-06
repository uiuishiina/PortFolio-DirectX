#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"DescriptorHeapAllocator.h"
#include"CurrentIndexBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// ディスクリプターヒープ活用クラス
		/// </summary>
		class DescriptorResource : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~DescriptorResource() {
				return_index();
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ディスクリプターヒープ参照取得関数
			/// </summary>
			/// <returns>取得したディスクリプターヒープ参照</returns>
			[[nodiscard]] ID3D12DescriptorHeap* get_heap() const noexcept {
				return allocator_->get_heap()->get();
			}

			/// <summary>
			/// ディスクリプターハンドル補助構造体取得関数
			/// </summary>
			/// <param name="index">取得するインデックス</param>
			/// <returns>取得したディスクリプターハンドル補助構造体... ないなら[ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Helper::DescriptorHeapHandles> get_handles(std::size_t index) const noexcept {

				if (handles_vec.size() <= index) {
					return std::nullopt;
				}

				return handles_vec[index];
			}

			[[nodiscard]] std::size_t get_handles_vec_size() const noexcept {
				return handles_vec.size();
			}

		protected:
			/* ========== Protectedメンバー関数 ========== */

			/// <summary>
			/// リソース初期化関数
			/// </summary>
			/// <param name="allocator">ディスクリプターヒープアロケーター参照</param>
			/// <returns>初期化の成否</returns>
			[[nodiscard]] HRESULT initialize_resource(
				DescriptorHeapAllocator* allocator,
				const CurrentIndexBase* index
			) {

				if (allocator == nullptr) {
					return E_INVALIDARG;
				}

				return_index();
				handles_vec.clear();

				allocator_ = allocator;

				for (std::size_t i = 0; i < index->get_size(); ++i) {

					const auto index = allocator->allocate_index();
					if (!index.has_value()) {

						return_index();
						return E_OUTOFMEMORY;
					}

					index_vec.push_back(index.value());
				
					handles_vec.push_back(
						allocator_->get_heap()->get_handles(index.value())
					);
				}

				return S_OK;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// 確保したインデックス
			/// </summary>
			std::vector<std::size_t> index_vec{};

			/// <summary>
			/// アロケーター参照
			/// </summary>
			DescriptorHeapAllocator* allocator_{};

			/// <summary>
			/// ディスクリプターハンドル補助構造体配列
			/// </summary>
			std::vector<Helper::DescriptorHeapHandles> handles_vec{};

			/// <summary>
			/// インデックス返還関数
			/// </summary>
			void return_index() {

				for (auto& index : index_vec) {
					allocator_->return_index(index);
				}
			}
		};
	}
}