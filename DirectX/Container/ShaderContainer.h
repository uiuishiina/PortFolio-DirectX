#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Container/UniqueptrKeyMap.h"

//	DirectX
#include"../ClassObject/ShaderCompiler.h"

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
		/// シェーダー倫理キー
		/// </summary>
		struct ShaderKey : public HandyItems::container::handle::LogicalKey {

			ShaderKey() = default;

			explicit ShaderKey(const char* key_name) :

				HandyItems::container::handle::LogicalKey{
				static_cast<std::uint32_t>(
					HandyItems::id::get_id::get_name_id<ShaderKey>(key_name)
					)
			} {}
		};

		/// <summary>
		/// シェーダー保存キー
		/// </summary>
		struct ShaderEncodeKey : public HandyItems::container::handle::EncodedKey {};


		/* ========== コンテナ ========== */

		/// <summary>
		/// シェーダーコンテナ
		/// </summary>
		class ShaderContainer : HandyItems::container::UniqueptrKeyMap
			<
			ShaderKey,
			ShaderEncodeKey,
			ClassObject::ShaderCompiler
			> 
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ShaderContainer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~ShaderContainer() = default;

			/* ===== 追加関数 ===== */

			/// <summary>
			/// シェーダー追加関数
			/// </summary>
			/// <param name="key">紐付けるシェーダー倫理キー</param>
			/// <param name="shader">追加するシェーダーインスタンス</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_shader(
				ShaderKey key,
				std::unique_ptr<ClassObject::ShaderCompiler>&& shader
			) {

				return add_value(key, std::move(shader));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// シェーダー参照取得関数
			/// </summary>
			/// <param name="key">紐づいたシェーダー倫理キー</param>
			/// <returns>シェーダー参照</returns>
			[[nodiscard]] ClassObject::ShaderCompiler* get_shader(
				const ShaderKey& key
			) const noexcept {

				return get_unique(key);
			}

		};
	}
}