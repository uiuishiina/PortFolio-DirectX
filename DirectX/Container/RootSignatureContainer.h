#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Container/UniqueptrKeyMap.h"

//	DirectX
#include"../ClassObject/RootSignature.h"

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
		/// ルートシグネチャー倫理キー
		/// </summary>
		struct RootSignatureKey : public HandyItems::container::handle::LogicalKey {

			RootSignatureKey() = default;

			explicit RootSignatureKey(const char* key_name) :

				HandyItems::container::handle::LogicalKey{
				static_cast<std::uint32_t>(
					HandyItems::id::get_id::get_name_id<RootSignatureKey>(key_name)
					)
			} {}
		};

		/// <summary>
		/// ルートシグネチャー保存キー
		/// </summary>
		struct RootSignatureKeyEncodeKey : public HandyItems::container::handle::EncodedKey {};


		/* ========== コンテナ ========== */

		/// <summary>
		/// ルートシグネチャーコンテナ
		/// </summary>
		class RootSignatureContainer : HandyItems::container::UniqueptrKeyMap
			<
			RootSignatureKey,
			RootSignatureKeyEncodeKey,
			ClassObject::RootSignature
			>
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			RootSignatureContainer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~RootSignatureContainer() = default;

			/* ===== 追加関数 ===== */

			/// <summary>
			/// ルートシグネチャー追加関数
			/// </summary>
			/// <param name="key">紐づけるルートシグネチャー倫理キー</param>
			/// <param name="root">追加するルートシグネチャーインスタンス</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_root_signature(
				RootSignatureKey key,
				std::unique_ptr<ClassObject::RootSignature>&& root
			) {

				return add_value(key, std::move(root));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ルートシグネチャー参照取得関数
			/// </summary>
			/// <param name="key">紐づいたルートシグネチャー倫理キー</param>
			/// <returns>ルートシグネチャー参照</returns>
			[[nodiscard]] ClassObject::RootSignature* get_root_signature(
				const RootSignatureKey& key
			) const noexcept {

				return get_unique(key);
			}

		};
	}
}