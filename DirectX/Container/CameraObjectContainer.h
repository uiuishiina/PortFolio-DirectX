#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Container/UniqueptrKeyMap.h"

//	DirectX
#include"../ClassModule/DrawObject/CameraObject.h"

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
		/// カメラオブジェクト倫理キー
		/// </summary>
		struct CameraObjectKey : public HandyItems::container::handle::LogicalKey {

			CameraObjectKey() = default;

			explicit CameraObjectKey(const char* key_name) :

				HandyItems::container::handle::LogicalKey{
				static_cast<std::uint32_t>(
					HandyItems::id::get_id::get_name_id<CameraObjectKey>(key_name)
					)
			} {}
		};

		/// <summary>
		/// カメラオブジェクト保存キー
		/// </summary>
		struct CameraObjectEncodeKey : public HandyItems::container::handle::EncodedKey {};


		/* ========== コンテナ ========== */


		/// <summary>
		/// カメラオブジェクトコンテナ
		/// </summary>
		class CameraObjectContainer : HandyItems::container::UniqueptrKeyMap
			<
			CameraObjectKey,
			CameraObjectEncodeKey,
			ClassModule::CameraObject
			>
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			CameraObjectContainer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~CameraObjectContainer() = default;

			/* ===== 追加関数 ===== */

			/// <summary>
			/// カメラオブジェクト追加関数
			/// </summary>
			/// <param name="key">紐づけるカメラオブジェクト倫理キー</param>
			/// <param name="obj">追加するカメラオブジェクトインスタンス</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_camera_object(
				CameraObjectKey key,
				std::unique_ptr<ClassModule::CameraObject>&& obj
			) {

				return add_value(key, std::move(obj));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// カメラオブジェクト参照取得関数
			/// </summary>
			/// <param name="key">紐づいたカメラオブジェクト倫理キー</param>
			/// <returns>カメラオブジェクト参照</returns>
			[[nodiscard]] ClassModule::CameraObject* get_camera_object(
				const CameraObjectKey& key
			) const noexcept {

				return get_unique(key);
			}

		};

	}
}