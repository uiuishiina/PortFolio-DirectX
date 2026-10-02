#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Container/UniqueptrKeyMap.h"

//	DirectX
#include"../ClassModule/DrawObject/DrawObjectBase.h"

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
		/// 描画オブジェクト倫理キー
		/// </summary>
		struct DrawObjectKey : public HandyItems::container::handle::LogicalKey {

			DrawObjectKey() = default;

			explicit DrawObjectKey(const char* key_name) :

				HandyItems::container::handle::LogicalKey{
				static_cast<std::uint32_t>(
					HandyItems::id::get_id::get_name_id<DrawObjectKey>(key_name)
					)
			} {}
		};

		/// <summary>
		/// 描画オブジェクト保存キー
		/// </summary>
		struct DrawObjectEncodeKey : public HandyItems::container::handle::EncodedKey {};


		/* ========== コンテナ ========== */

		/// <summary>
		/// 描画オブジェクトコンテナ
		/// </summary>
		class DrawObjectContainer : HandyItems::container::UniqueptrKeyMap
			<
			DrawObjectKey,
			DrawObjectEncodeKey,
			ClassModule::DrawObjectBase
			>
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DrawObjectContainer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DrawObjectContainer() = default;

			/* ===== 追加関数 ===== */

			/// <summary>
			/// 描画オブジェクト追加関数
			/// </summary>
			/// <param name="key">紐づける描画オブジェクト倫理キー</param>
			/// <param name="pass">追加する描画オブジェクトインスタンス</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_draw_object(
				DrawObjectKey key,
				std::unique_ptr<ClassModule::DrawObjectBase>&& pass
			) {

				return add_value(key, std::move(pass));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// 描画オブジェクト参照取得関数
			/// </summary>
			/// <param name="key">紐づいた描画オブジェクト倫理キー</param>
			/// <returns>描画オブジェクト参照</returns>
			[[nodiscard]] ClassModule::DrawObjectBase* get_draw_object(
				const DrawObjectKey& key
			) const noexcept {

				return get_unique(key);
			}

		};
	}
}