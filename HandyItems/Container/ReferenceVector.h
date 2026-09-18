#pragma once
#include"ReferenceContainerBase.h"
#include<vector>

/// <summary>
/// 便利用名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// コンテナ用名前空間
	/// </summary>
	namespace container {

		/* ========== 参照保存配列クラス定義 ========== */

		/// <summary>
		/// 参照保存配列クラス
		/// </summary>
		/// <typeparam name="T">配列に保存したい型</typeparam>
		template<typename T>
		class ReferenceVector : public ReferenceContainerBase<T>
		{
		public:
			/* =============== クラス設定 =============== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ReferenceVector() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~ReferenceVector() = default;


			/* =============== 追加関数 =============== */

			/// <summary>
			/// 参照追加関数
			/// </summary>
			/// <param name="value">追加する参照</param>
			void add_reference(T& value) override {
				reference_vector.push_back(value);
			}


			/* =============== 取得関数 =============== */

			/// <summary>
			/// 前方参照取得関数
			/// </summary>
			/// <returns>取得した参照...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_front_reference() override {

				//	キューがあるか
				if (reference_vector.empty()) {
					return std::nullopt;
				}

				return reference_vector.front();
			}

			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_front_reference() const override {

				//	キューがあるか
				if (reference_vector.empty()) {
					return std::nullopt;
				}

				return reference_vector.front();
			}

			/// <summary>
			/// 後方参照取得関数
			/// </summary>
			/// <returns>取得した参照...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_back_reference() override {

				//	キューがあるか
				if (reference_vector.empty()) {
					return std::nullopt;
				}

				return reference_vector.back();
			}

			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_back_reference() const override {

				//	キューがあるか
				if (reference_vector.empty()) {
					return std::nullopt;
				}

				return reference_vector.back();
			}

			/// <summary>
			/// インデックス参照取得関数
			/// </summary>
			/// <param name="index">取得したい参照インデックス</param>
			/// <returns>取得した参照...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_reference_to_index(std::size_t index) override {

				if (reference_vector.empty()) {
					return std::nullopt;
				}

				return reference_vector[index];
			}

			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_reference_to_index(std::size_t index) const override {

				if (reference_vector.empty()) {
					return std::nullopt;
				}

				return reference_vector[index];
			}

		private:
			/* =============== メンバー変数 =============== */

			/// <summary>
			/// 参照保存配列
			/// </summary>
			std::vector<std::reference_wrapper<T>> reference_vector{};

		};
	}
}