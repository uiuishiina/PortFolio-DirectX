#pragma once
#include<optional>
#include<functional>
#include<ranges>
#include<concepts>

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// コンテナ用名前空間
	/// </summary>
	namespace container {

		/* ========== 参照コンテナ基底クラス定義 ========== */

		/// <summary>
		/// 参照コンテナ基底クラス
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template<typename T>
		class ReferenceContainerBase
		{
		public:
			/* =============== クラス設定 =============== */

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~ReferenceContainerBase() = default;


			/* =============== 追加関数 =============== */

			/// <summary>
			/// 参照追加関数
			/// </summary>
			/// <param name="value">追加する参照</param>
			virtual void add_reference(T& value) = 0;

			/// <summary>
			/// 参照配列追加関数
			/// </summary>
			/// <typeparam name="R">参照型配列</typeparam>
			/// <param name="value">追加する参照配列</param>
			template<std::ranges::range R>
				requires std::same_as<std::remove_cvref_t<std::ranges::range_reference_t<R>>, T>
			void add_references(R& value) {
				for (auto& p : value) {
					add_reference(p);
				}
			}

			/* =============== 取得関数 =============== */

			/// <summary>
			/// 前方参照取得関数
			/// </summary>
			/// <returns>取得した参照...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] virtual std::optional<std::reference_wrapper<T>> get_front_reference() = 0;
			[[nodiscard]] virtual std::optional<std::reference_wrapper<T>> get_front_reference() const = 0;

			/// <summary>
			/// 後方参照取得関数
			/// </summary>
			/// <returns>取得した参照...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] virtual std::optional<std::reference_wrapper<T>> get_back_reference() = 0;
			[[nodiscard]] virtual std::optional<std::reference_wrapper<T>> get_back_reference() const = 0;

			/// <summary>
			/// インデックス参照取得関数
			/// </summary>
			/// <param name="index">取得したい参照インデックス</param>
			/// <returns>取得した参照...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] virtual std::optional<std::reference_wrapper<T>> get_reference_to_index(std::size_t index) = 0;
			[[nodiscard]] virtual std::optional<std::reference_wrapper<T>> get_reference_to_index(std::size_t index) const = 0;

		protected:
			/* =============== クラス設定 =============== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ReferenceContainerBase() = default;

		};
	}
}