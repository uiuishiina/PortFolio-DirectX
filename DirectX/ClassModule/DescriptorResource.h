#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"DescriptorHeapAllocator.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		namespace State {

			enum class HeapState {
				Static,
				Buffering,
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
				else if (state_ == State::HeapState::Buffering) {
					return initialize_buffering(allocator);
				}
				else if (state_ == State::HeapState::Frame) {
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
			/// ディスクリプターハンドル補助構造体取得関数
			/// </summary>
			/// <param name="index">取得するインデックス</param>
			/// <returns>取得したディスクリプターハンドル補助構造体... ないなら[ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Helper::DescriptorHeapHandles> get_handles(std::size_t index) const noexcept {

				if (vec_size <= index) {
					return std::nullopt;
				}

				return handles_vec[index];
			}

			[[nodiscard]] std::size_t get_handles_vec_size() const noexcept {
				return vec_size;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ステート設定
			/// </summary>
			State::HeapState state_{};

			/// <summary>
			/// 確保したインデックス
			/// </summary>
			std::size_t index_{};

			/// <summary>
			/// 初期化フラグ
			/// </summary>
			bool is_initialized = false;

			/// <summary>
			/// アロケーター参照
			/// </summary>
			DescriptorHeapAllocator* allocator_{};

			/// <summary>
			/// ディスクリプターハンドル補助構造体配列
			/// </summary>
			std::vector<Helper::DescriptorHeapHandles> handles_vec{};

			/// <summary>
			/// 配列サイズキャッシュ
			/// </summary>
			std::size_t vec_size{};

			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// 静的ヒープ初期化関数
			/// </summary>
			/// <param name="allocator"></param>
			/// <returns></returns>
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

				vec_size = handles_vec.size();
				is_initialized = true;

				return S_OK;
			}

			/// <summary>
			/// バッファリング別ヒープ初期化関数
			/// </summary>
			/// <param name="allocator"></param>
			/// <returns></returns>
			[[nodiscard]] HRESULT initialize_buffering(
				DescriptorHeapAllocator* allocator
			) {

				const auto index = allocator->allocate_buffering_index();
				if (!index.has_value()) {
					return E_OUTOFMEMORY;
				}

				index_ = index.value();
				allocator_ = allocator;

				const auto static_range = allocator_->get_static_range();

				for (UINT i = 0; i < allocator_->get_back_buffer_size(); ++i) {

					handles_vec.push_back(
						allocator_->get_heap()->get_handles(
							static_range + (i * allocator_->get_one_buffering_range()) + index_
						));
				}

				vec_size = handles_vec.size();
				is_initialized = true;

				return S_OK;
			}


			/// <summary>
			/// フレーム別ヒープ初期化関数
			/// </summary>
			/// <param name="allocator"></param>
			/// <returns></returns>
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
				const auto buffering_range = allocator_->get_one_buffering_range() * allocator_->get_back_buffer_size();

				for (UINT i = 0; i < allocator_->get_frame_resource_size(); ++i) {

					handles_vec.push_back(
						allocator_->get_heap()->get_handles(
							static_range + buffering_range + (i * allocator_->get_one_frame_range()) + index_
						));
				}

				vec_size = handles_vec.size();
				is_initialized = true;

				return S_OK;
			}

			/// <summary>
			/// インデックス返還関数
			/// </summary>
			void return_index() {

				if (is_initialized) {
					if (state_ == State::HeapState::Static) {
						allocator_->return_static_index(index_);
					}
					else if (state_ == State::HeapState::Buffering) {
						allocator_->return_buffering_index(index_);
					}
					else if (state_ == State::HeapState::Frame) {
						allocator_->return_frame_index(index_);
					}

					is_initialized = false;
				}
			}
		};
	}
}