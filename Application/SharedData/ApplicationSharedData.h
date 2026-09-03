#pragma once
#include"Container/ReferenceVector.h"
#include"Tuple/TupleBase.h"
#include"Others/NonCopyableBase.h"
#include"Container/UnorderedMapBase.h"
#include<any>
#include<typeindex>


/// <summary>
/// 共有データ名前空間
/// </summary>
namespace sharedData {

	/// <summary>
	/// アプリケーションデータシェアクラス
	/// </summary>
	class ApplicationSharedData final : public others::NonCopyableBase
	{
	public:
		/* ========== クラス設定 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		ApplicationSharedData() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~ApplicationSharedData() = default;


		/* ========== 追加関数 ========== */

		/// <summary>
		/// シェアデータ型追加関数
		/// </summary>
		/// <details>
		/// [ 参照保存配列 ] になった状態で保存される
		/// </details>
		/// <typeparam name="T">追加したいデータ型</typeparam>
		/// <returns>追加の成否</returns>
		template<typename T>
		bool add_share_data() {
			return data_map.add_value(typeid(T), HandyItems::container::ReferenceVector<T>{});
		}


		/* ========== 取得関数 ========== */

		/// <summary>
		/// シェアデータ配列取得関数
		/// </summary>
		/// <typeparam name="T">取得したいデータ型</typeparam>
		/// <returns>取得した [ データ型参照保存配列 ]... ないなら [ nullptr ]</returns>
		template<typename T>
		[[nodiscard]] HandyItems::container::ReferenceVector<T>* get_share_data() {

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
};