#pragma once
#include<concepts>

/// <summary>
/// 便利用名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// 列挙体名前空間
	/// </summary>
	namespace Enum {

		/// <summary>
		/// テンプレートコンセプト定義用名前空間
		/// </summary>
		namespace concepts {

			/// <summary>
			/// 列挙体指定コンセプト
			/// </summary>
			template<typename T>
			concept IsEnum = std::is_enum_v<T>;

			/// <summary>
			/// 列挙体カウントコンセプト
			/// </summary>
			/// <details>
			/// [ 列挙体 ] かつ [ Countが定義されている ]
			/// 定義されている数を数えるために作成
			/// </details>
			template<typename T>
			concept EnumHasCount = std::is_enum_v <T>
				&& requires { T::Count; };

		}

		/// <summary>
		/// 列挙体変換関数
		/// </summary>
		/// <param name="value">変換する列挙体変数</param>
		/// <returns>変換した値</returns>
		template<concepts::IsEnum T>
		[[nodiscard]] static constexpr std::size_t enum_to_index(const T& value) {
			return static_cast<std::size_t>(value);
		}
	}

	/// <summary>
	/// お試し用(利用時削除推奨)
	/// </summary>
	enum hogehoge {
		A,
		B,
		C,

		Count
	};
}