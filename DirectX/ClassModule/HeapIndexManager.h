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
			/// ヒープインデックスマネージャー設定構造体
			/// </summary>
			struct HeapIndexManagerDesc {

				/// <summary>
				/// 静的ヒープサイズ
				/// </summary>
				UINT static_range{};

				/// <summary>
				/// 単体フレームヒープサイズ
				/// </summary>
				UINT one_frame_range{};

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
		/// ヒープインデックスマネージャー
		/// </summary>
		class HeapIndexManager final : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			HeapIndexManager() {

				heap_ = std::make_unique<ClassObject::DescriptorHeap>();
			}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~HeapIndexManager() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// ディスクリプターヒープ作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="desc">ヒープインデックスマネージャー設定構造体参照</param>
			/// <param name="frame_resource_size">フレームリソースサイズ</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_heap(
				ID3D12Device* device_,
				const desc::HeapIndexManagerDesc& desc,
				UINT frame_resource_size
			) {

				//	フレームリソースサイズチェック
				if (frame_resource_size == 0) {
					return E_INVALIDARG;
				}

				//	ディスクリプターヒープサイズ取得
				const auto heap_size = desc.static_range + (
					desc.one_frame_range * frame_resource_size
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
				one_frame_range = desc.one_frame_range;
				max_heap_size = heap_size;

				//	キュー初期化
				for (std::size_t i = 0; i < static_range; i++) {
					free_static_index.push(i);
				}
				for (std::size_t i = 0; i < one_frame_range; i++) {
					free_frame_index.push(i);
				}

				return hr;
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ディスクリプターヒープ参照取得関数
			/// </summary>
			/// <returns>取得したディスクリプターヒープ参照</returns>
			[[nodiscard]] ClassObject::DescriptorHeap* get_heap() const noexcept {

				return heap_.get();
			}

			/// <summary>
			/// 静的ヒープインデックス取得関数
			/// </summary>
			/// <returns>取得したインデックス... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::size_t> allocate_static_index() {

				return free_static_index.pop();
			}

			/// <summary>
			/// フレームヒープインデックス取得関数
			/// </summary>
			/// <returns>取得したインデックス... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::size_t> allocate_frame_index() {

				return free_frame_index.pop();
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
			}

			/// <summary>
			/// フレームヒープインデックス返還関数
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
			/// フレームヒープフリーインデックスキュー
			/// </summary>
			HandyItems::container::Queue<std::size_t> free_frame_index{};

			/// <summary>
			/// 静的ヒープサイズ
			/// </summary>
			UINT static_range{};

			/// <summary>
			/// 単体フレームヒープサイズ
			/// </summary>
			UINT one_frame_range{};

			/// <summary>
			/// 全体ヒープサイズ
			/// </summary>
			UINT max_heap_size{};

		};
	}
}