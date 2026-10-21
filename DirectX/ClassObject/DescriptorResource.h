#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassObject/DescriptorHeapAllocator.h"


/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		namespace State {

			enum class HeapState {
				Static,
				Frame
			};
		}

		/// <summary>
		/// ディスクリプターヒープ活用クラス
		/// </summary>
		class DescriptorResource : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DescriptorResource() = delete;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="state">HeapState設定</param>
			DescriptorResource(
				State::HeapState state
			) :
				state_{ state } {}

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~DescriptorResource() {
				return_index();
			}

		protected:
			/* ========== Protectedメンバー関数 ========== */

			/// <summary>
			/// リソース初期化関数
			/// </summary>
			/// <param name="allocator">ディスクリプターヒープアロケーター参照</param>
			/// <returns>初期化の成否</returns>
			[[nodiscard]] HRESULT initialize_resource(
				DescriptorHeapAllocator* allocator
			) {

				if (allocator == nullptr) {
					return E_INVALIDARG;
				}

				return_index();

				handles_vec.clear();

				if (state_ == State::HeapState::Static) {
					return initialize_static(allocator);
				}
				else {
					return initialize_frame(allocator);
				}
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
			/// ディスクリプターハンドル補助構造体配列参照取得関数
			/// </summary>
			/// <returns>取得したディスクリプターハンドル補助構造体配列参照</returns>
			[[nodiscard]] const std::vector<Helper::DescriptorHeapHandles>& get_handles_vec() const noexcept {
				return handles_vec;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			State::HeapState state_{};

			std::size_t index_{};

			bool is_initialized = false;

			DescriptorHeapAllocator* allocator_{};

			std::vector<Helper::DescriptorHeapHandles> handles_vec{};

			/* ========== Privateメンバー関数 ========== */

			[[nodiscard]] HRESULT initialize_static(
				DescriptorHeapAllocator* allocator
			) {

				const auto index = allocator->allocate_static_index();
				if (!index.has_value()) {
					return E_OUTOFMEMORY;
				}

				index_ = index.value();
				allocator_ = allocator;

				handles_vec.push_back(
					allocator_->get_heap()->get_handles(index_)
				);

				is_initialized = true;

				return S_OK;
			}

			[[nodiscard]] HRESULT initialize_frame(
				DescriptorHeapAllocator* allocator
			) {

				const auto index = allocator->allocate_frame_index();
				if (!index.has_value()) {
					return E_OUTOFMEMORY;
				}

				index_ = index.value();
				allocator_ = allocator;

				const auto static_range = allocator_->get_static_range();

				for (UINT i = 0; i < allocator_->get_frame_resource_size(); ++i) {

					handles_vec.push_back(
						allocator_->get_heap()->get_handles(
							static_range + (i * allocator_->get_frame_range()) + index_
						));
				}

				is_initialized = true;

				return S_OK;
			}


			void return_index() {

				if (is_initialized) {
					if (state_ == State::HeapState::Static) {
						allocator_->return_static_index(index_);
					}
					else {
						allocator_->return_frame_index(index_);
					}
					is_initialized = false;
				}
			}
		};
	}
}