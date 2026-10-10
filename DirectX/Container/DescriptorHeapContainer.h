#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Container/UniqueptrKeyMap.h"

//	DirectX
#include"../ClassObject/DescriptorHeap.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// コンテナ名前空間
	/// </summary>
	namespace Container {

		/* ========== ハッシュキー ========== */

		/// <summary>
		/// ディスクリプターヒープ倫理キー
		/// </summary>
		struct DescriptorHeapKey : public HandyItems::container::handle::LogicalKey {

			DescriptorHeapKey() = default;

			explicit DescriptorHeapKey(const char* key_name) :

				HandyItems::container::handle::LogicalKey{
				static_cast<std::uint32_t>(
					HandyItems::id::get_id::get_name_id<DescriptorHeapKey>(key_name)
					)
			} {}
		};

		/// <summary>
		/// ディスクリプターヒープ保存キー
		/// </summary>
		struct DescriptorHeapKeyEncodeKey : public HandyItems::container::handle::EncodedKey {};


		/* ========== コンテナ ========== */

		/// <summary>
		/// ディスクリプターヒープコンテナ
		/// </summary>
		class DescriptorHeapContainer : HandyItems::container::UniqueptrKeyMap
			<
			DescriptorHeapKey,
			DescriptorHeapKeyEncodeKey,
			ClassObject::DescriptorHeap
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
			/// <param name="heap">追加するディスクリプターヒープインスタンス</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_descriptor_heap(
				DescriptorHeapKey key,
				std::unique_ptr<ClassObject::DescriptorHeap>&& heap
			) {

				return add_value(key, std::move(heap));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ディスクリプターヒープ参照取得関数
			/// </summary>
			/// <param name="key">紐づいたディスクリプターヒープ倫理キー</param>
			/// <returns>ディスクリプターヒープ参照</returns>
			[[nodiscard]] ClassObject::DescriptorHeap* get_descriptor_heap(
				const DescriptorHeapKey& key
			) const noexcept {

				return get_unique(key);
			}

		};
	}
}