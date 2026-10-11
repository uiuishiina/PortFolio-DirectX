#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Container/UniqueptrKeyMap.h"

//	DirectX
#include"../ClassModule/HeapIndexManager.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// コンテナ名前空間
	/// </summary>
	namespace Container {

		[[nodiscard]] inline std::uintptr_t get_heap_type_id(
			D3D12_DESCRIPTOR_HEAP_TYPE heap_type
		) noexcept {

			return static_cast<std::uintptr_t>(heap_type);
		}

		/* ========== ハッシュキー ========== */

		/// <summary>
		/// ディスクリプターヒープ倫理キー
		/// </summary>
		struct DescriptorHeapKey : public HandyItems::container::handle::LogicalKey {

			DescriptorHeapKey() = default;

			explicit DescriptorHeapKey(D3D12_DESCRIPTOR_HEAP_TYPE key_type) :

				HandyItems::container::handle::LogicalKey{
				static_cast<std::uint32_t>(
					get_heap_type_id(key_type)
					)
			} {}
		};

		/// <summary>
		/// ディスクリプターヒープ保存キー
		/// </summary>
		struct DescriptorHeapKeyEncodeKey : public HandyItems::container::handle::EncodedKey {};


		/* ========== コンテナ ========== */

		/// <summary>
		/// ディスクリプターヒープインデックスマネージャーコンテナ
		/// </summary>
		class DescriptorHeapContainer : HandyItems::container::UniqueptrKeyMap
			<
			DescriptorHeapKey,
			DescriptorHeapKeyEncodeKey,
			ClassModule::HeapIndexManager
			>
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DescriptorHeapContainer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DescriptorHeapContainer() = default;

			/* ===== 追加関数 ===== */

			/// <summary>
			/// ディスクリプターヒープ追加関数
			/// </summary>
			/// <param name="key">紐づけるディスクリプターヒープ倫理キー</param>
			/// <param name="heap">追加するディスクリプターヒープインデックスマネージャーインスタンス</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_heap_manager(
				DescriptorHeapKey key,
				std::unique_ptr<ClassModule::HeapIndexManager>&& heap
			) {

				return add_value(key, std::move(heap));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ディスクリプターヒープ参照取得関数
			/// </summary>
			/// <param name="key">紐づいたディスクリプターヒープ倫理キー</param>
			/// <returns>ディスクリプターヒープ参照</returns>
			[[nodiscard]] ClassModule::HeapIndexManager* get_heap_manager(
				const DescriptorHeapKey& key
			) const noexcept {

				return get_unique(key);
			}

		};
	}
}