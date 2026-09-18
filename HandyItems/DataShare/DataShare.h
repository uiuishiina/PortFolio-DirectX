#pragma once

/* ========== Includeファイル ========== */

#include"Container/ReferenceVector.h"
#include"Others/NonCopyableBase.h"
#include"Container/UnorderedMapBase.h"
#include<any>
#include<typeindex>

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// 共有データ名前空間
	/// </summary>
	namespace DataShare {

		/// <summary>
		/// データシェアクラス
		/// </summary>
		/// <details>
		/// 共有するデータの [ 参照 ] をまとめるクラス
		/// </details>
		class DataShare : public others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DataShare() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~DataShare() = default;


			/* ===== 追加関数 ===== */

			/// <summary>
			/// シェアデータ型追加関数
			/// </summary>
			/// <details>
			/// [ 参照保存配列 ] になった状態で保存される
			/// </details>
			/// <typeparam name="T">追加したいデータ型</typeparam>
			/// <returns>追加の成否</returns>
			template<typename T>
			bool add_share_data_type() {

				return data_map.add_value(typeid(T), HandyItems::container::ReferenceVector<T>{});
			}


			/* ========== 取得関数 ========== */

			/// <summary>
			/// シェアデータ配列取得関数
			/// </summary>
			/// <typeparam name="T">取得したいデータ型</typeparam>
			/// <returns>取得した [ データ型参照保存配列 ]... ないなら [ nullptr ]</returns>
			template<typename T>
			[[nodiscard]] HandyItems::container::ReferenceVector<T>* get_share_data_type() {

				auto* data = data_map.get_value_p(typeid(T));
				if (data == nullptr) {
					return nullptr;
				}

				return std::any_cast<HandyItems::container::ReferenceVector<T>>(data);
			}

		private:
			/* ========== メンバー変数 ========== */

			/// <summary>
			/// シェアデータ保存コンテナクラス
			/// </summary>
			HandyItems::container::UnorderedMapBase<std::type_index, std::any> data_map{};

		};
	}
}