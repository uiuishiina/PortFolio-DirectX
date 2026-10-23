#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassObject/DescriptorHeap.h"

#include"Container/Queue.h"

#include<memory>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		namespace desc {

			/// <summary>
			/// ディスクリプターヒープアロケーター設定構造体
			/// </summary>
			struct DescriptorHeapAllocatorDesc {

				/// <summary>
				/// 静的ヒープサイズ
				/// </summary>
				std::size_t static_range{};

				/// <summary>
				/// バッファリング別ヒープサイズ
				/// </summary>
				std::size_t one_buffering_range{};

				/// <summary>
				/// フレームリソース別ヒープサイズ
				/// </summary>
				std::size_t one_frame_range{};

				/// <summary>
				/// ディスクリプターヒープタイプ設定
				/// </summary>
				D3D12_DESCRIPTOR_HEAP_TYPE type_{};

				/// <summary>
				/// シェーダー可視設定
				/// </summary>
				D3D12_DESCRIPTOR_HEAP_FLAGS flags_{};

				/// <summary>
				/// ノードマスク
				/// </summary>
				UINT node_{};

			};
		}

		/// <summary>
		/// ディスクリプターヒープアロケーター
		/// </summary>
		class DescriptorHeapAllocator final : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DescriptorHeapAllocator() {

				heap_ = std::make_unique<ClassObject::DescriptorHeap>();
			}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DescriptorHeapAllocator() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// ディスクリプターヒープ作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="desc">ヒープインデックスマネージャー設定構造体参照</param>
			/// <param name="resource_size">フレームリソースサイズ</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_heap(
				ID3D12Device* device_,
				const desc::DescriptorHeapAllocatorDesc& desc,
				UINT buffer_size,
				UINT resource_size
			) {

				//	サイズチェック
				if (resource_size == 0 || buffer_size == 0) {
					return E_INVALIDARG;
				}

				back_buffer_size = buffer_size;
				frame_resource_size = resource_size;

				//	ディスクリプターヒープサイズ取得
				const UINT heap_size = static_cast<UINT>(
					desc.static_range +
					(desc.one_buffering_range * back_buffer_size) +
					(desc.one_frame_range * frame_resource_size)
					);
				if (heap_size == 0) {
					return E_INVALIDARG;
				}

				//	ディスクリプターヒープ作成構造体作成
				ClassObject::desc::DescriptorHeapDesc heap_desc{
					desc.type_,
					heap_size,
					desc.flags_,
					desc.node_
				};

				//	ディスクリプターヒープ作成
				const auto hr = heap_->create_descriptor_heap(
					device_,
					heap_desc
				);
				if (FAILED(hr)) {
					return hr;
				}

				//	変数設定
				static_range = desc.static_range;
				one_buffering_range = desc.one_buffering_range;
				one_frame_range = desc.one_frame_range;
				max_heap_size = heap_size;

				//	キュー初期化
				for (std::size_t i = 0; i < static_range; i++) {
					free_static_index.push(i);
				}
				for (std::size_t i = 0; i < one_buffering_range; i++) {
					free_buffering_index.push(i);
				}
				for (std::size_t i = 0; i < one_frame_range; i++) {
					free_frame_index.push(i);
				}

				return hr;
			}

			/* ===== 取得関数 ===== */

			/* -- 参照 -- */

			/// <summary>
			/// ディスクリプターヒープ参照取得関数
			/// </summary>
			/// <returns>取得したディスクリプターヒープ参照</returns>
			[[nodiscard]] ClassObject::DescriptorHeap* get_heap() const noexcept {

				return heap_.get();
			}


			/* -- インデックス -- */

			/// <summary>
			/// 静的ヒープインデックス取得関数
			/// </summary>
			/// <returns>取得したインデックス... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::size_t> allocate_static_index() {

				return free_static_index.pop();
			}

			/// <summary>
			/// バッファリング別ヒープインデックス取得関数
			/// </summary>
			/// <returns>取得したインデックス... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::size_t> allocate_buffering_index() {

				return free_buffering_index.pop();
			}

			/// <summary>
			/// フレームリソース別ヒープインデックス取得関数
			/// </summary>
			/// <returns>取得したインデックス... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::size_t> allocate_frame_index() {

				return free_frame_index.pop();
			}
			

			/* -- サイズ設定 -- */

			/// <summary>
			/// 静的ヒープサイズ取得関数
			/// </summary>
			/// <returns>静的ヒープサイズ</returns>
			[[nodiscard]] std::size_t get_static_range() const noexcept {
				return static_range;
			}

			/// <summary>
			/// バッファリング別ヒープサイズ取得関数
			/// </summary>
			/// <returns>バッファリング別ヒープサイズ</returns>
			[[nodiscard]] std::size_t get_one_buffering_range() const noexcept {
				return one_buffering_range;
			}

			/// <summary>
			/// フレームリソース別ヒープサイズ取得関数
			/// </summary>
			/// <returns>フレームリソース別ヒープサイズ</returns>
			[[nodiscard]] std::size_t get_one_frame_range() const noexcept {
				return one_frame_range;
			}

			/// <summary>
			/// バッファリングサイズ取得関数
			/// </summary>
			/// <returns>バッファリングサイズ</returns>
			[[nodiscard]] std::size_t get_back_buffer_size() const noexcept {
				return back_buffer_size;
			}
			/// <summary>
			/// フレームリソースサイズ取得関数
			/// </summary>
			/// <returns>フレームリソースサイズ</returns>
			[[nodiscard]] std::size_t get_frame_resource_size() const noexcept {
				return frame_resource_size;
			}


			/* ===== 追加関数 ===== */

			/// <summary>
			/// 静的ヒープインデックス返還関数
			/// </summary>
			/// <param name="index">返還するインデックス</param>
			/// <returns>返還の成否</returns>
			bool return_static_index(
				std::size_t index
			) {

				if (index >= static_range) {
					return false;
				}

				free_static_index.push(index);

				return true;
			}

			/// <summary>
			/// バッファリング別ヒープインデックス返還関数
			/// </summary>
			/// <param name="index">返還するインデックス</param>
			/// <returns>返還の成否</returns>
			bool return_buffering_index(
				std::size_t index
			) {

				if (index >= one_buffering_range) {
					return false;
				}

				free_buffering_index.push(index);

				return true;
			}
			/// <summary>
			/// フレームリソース別ヒープインデックス返還関数
			/// </summary>
			/// <param name="index">返還するインデックス</param>
			/// <returns>返還の成否</returns>
			bool return_frame_index(
				std::size_t index
			) {

				if (index >= one_frame_range) {
					return false;
				}

				free_frame_index.push(index);

				return true;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ディスクリプターヒープクラスインスタンス
			/// </summary>
			std::unique_ptr<ClassObject::DescriptorHeap> heap_{};

			/// <summary>
			/// 静的ヒープフリーインデックスキュー
			/// </summary>
			HandyItems::container::Queue<std::size_t> free_static_index{};

			/// <summary>
			/// バッファリング別ヒープフリーインデックスキュー
			/// </summary>
			HandyItems::container::Queue<std::size_t> free_buffering_index{};

			/// <summary>
			/// フレームリソース別ヒープフリーインデックスキュー
			/// </summary>
			HandyItems::container::Queue<std::size_t> free_frame_index{};


			/// <summary>
			/// 静的ヒープサイズ
			/// </summary>
			std::size_t static_range{};

			/// <summary>
			/// バッファリング別ヒープサイズ
			/// </summary>
			std::size_t one_buffering_range{};

			/// <summary>
			/// フレームリソース別ヒープサイズ
			/// </summary>
			std::size_t one_frame_range{};

			/// <summary>
			/// 全体ヒープサイズ
			/// </summary>
			UINT max_heap_size{};


			/// <summary>
			/// バッファリングサイズ
			/// </summary>
			UINT back_buffer_size{};

			/// <summary>
			/// フレームリソースサイズ
			/// </summary>
			UINT frame_resource_size{};

		};
	}
}