#pragma once
#pragma once
#include<tuple>

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// タプル名前空間
	/// </summary>
	namespace tuple {

		template<typename... Args>
		class TupleBase
		{
		public:
			/* ===== メンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			TupleBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~TupleBase() = default;


			/* ===== 取得関数 ===== */

			/// <summary>
			/// メンバー参照取得関数
			/// </summary>
			/// <typeparam name="T">取得したい型</typeparam>
			/// <returns>取得した値</returns>
			template<typename T>
			[[nodiscard]] T& get_value() noexcept {
				return std::get<T>(data_);
			}

			/// <summary>
			/// メンバー参照取得関数
			/// </summary>
			/// <typeparam name="T">取得したい型</typeparam>
			/// <returns>取得した値</returns>
			template<typename T>
			[[nodiscard]] const T& get_value()const noexcept {
				return std::get<T>(data_);
			}

			/// <summary>
			/// メンバーコピー取得関数
			/// </summary>
			/// <typeparam name="T">取得したい型</typeparam>
			/// <returns>取得した値</returns>
			template<typename T>
			[[nodiscard]] T get_value_copy() {
				return std::get<T>(data_);
			}

		private:

			/// <summary>
			/// タプル変数
			/// </summary>
			std::tuple<Args...> data_;

		};
	}
}