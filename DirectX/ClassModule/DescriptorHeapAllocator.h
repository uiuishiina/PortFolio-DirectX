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
			DescriptorHeapAllocator() :
				heap_{ std::make_unique<ClassObject::DescriptorHeap>() } {}

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

				//	ディスクリプターヒープサイズ取得
				const UINT heap_size = static_cast<UINT>(
					desc.static_range +
					(desc.one_buffering_range * buffer_size) +
					(desc.one_frame_range * resource_size)
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
				max_heap_size = heap_size;

				//	キュー初期化
				for (UINT i = 0; i < heap_size; i++) {
					free_index.push(static_cast<std::size_t>(i));
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

			/// <summary>
			/// ヒープインデックス取得関数
			/// </summary>
			/// <returns>取得したインデックス... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::size_t> allocate_index() {

				return free_index.pop();
			}

			/* ===== 追加関数 ===== */

			/// <summary>
			/// ヒープインデックス返還関数
			/// </summary>
			/// <param name="index">返還するインデックス</param>
			/// <returns>返還の成否</returns>
			bool return_index(
				std::size_t index
			) {

				if (index >= static_cast<std::size_t>(max_heap_size)) {
					return false;
				}

				free_index.push(index);

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
			HandyItems::container::Queue<std::size_t> free_index{};

			/// <summary>
			/// 全体ヒープサイズ
			/// </summary>
			UINT max_heap_size{};

		};
	}
}