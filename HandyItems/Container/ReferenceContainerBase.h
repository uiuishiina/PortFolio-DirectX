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
		/// <typeparam name="T">コンテナに保存する型</typeparam>
		template<typename T>
		class ReferenceContainerBase
		{
		public:
			/* =============== メンバー関数 =============== */

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~ReferenceContainerBase() = default;


			/* =============== 追加純粋仮想関数 =============== */

			/// <summary>
			/// 参照追加関数
			/// </summary>
			/// <param name="value">追加する参照</param>
			virtual void add_reference(
				T& value
			) = 0;

			/// <summary>
			/// 参照配列追加関数
			/// </summary>
			/// <typeparam name="R">追加する配列型</typeparam>
			/// <param name="value">追加する配列</param>
			template<std::ranges::range R>
				requires std::same_as<std::remove_cvref_t<std::ranges::range_reference_t<R>>, T>
			virtual void add_references(
				R& value
			);

			/* =============== 取得純粋仮想関数 =============== */

			/// <summary>
			/// 参照取得関数
			/// </summary>
			/// <returns>取得した参照...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] virtual std::optional<std::reference_wrapper<T>> get_reference() = 0;

		protected:

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ReferenceContainerBase() = default;

		};
	}
}