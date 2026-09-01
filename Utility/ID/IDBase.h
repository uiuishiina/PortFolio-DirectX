#pragma once
#include<cstdint>


/// <summary>
/// 便利用名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// ID名前空間
	/// </summary>
	namespace id {

		/* ========== ID取得関数定義 ========== */

		/// <summary>
		/// ID取得名前空間
		/// </summary>
		namespace get_id {

			/// <summary>
			/// タイプ型ID取得関数
			/// </summary>
			/// <details>
			/// 実行毎に値が変わるため注意
			/// </details>
			/// <typeparam name="T">IDを取得したい型</typeparam>
			/// <returns>型から取得したID</returns>
			template<typename T>
			[[nodiscard]] static std::uintptr_t get_type_id() noexcept {
				static const char value{};
				return reinterpret_cast<std::uintptr_t>(&value);
			}


			/// <summary>
			/// 文字列ID取得関数
			/// </summary>
			/// <details>
			/// 文字列を利用して識別用IDを作成する
			/// [ T型 ] は識別用IDを利用する型
			/// </details>
			/// <typeparam name="T">IDを取得したい型</typeparam>
			/// <param name="value">IDを取得したい名前</param>
			/// <returns>名前から取得したID</returns>
			template<typename T>
			[[nodiscard]] constexpr std::uintptr_t get_name_id(const char* value) noexcept {

				std::uintptr_t hash = get_type_id<T>();

				while (*value != '\0') {
					hash ^= static_cast<unsigned char>(*value);
					hash *= 1099511628211ull;
					++value;
				}

				return hash;
			}
		}

		/* ========== ID組み合わせ関数定義 ========== */

		namespace make_id {

			/// <summary>
			/// ID合体関数
			/// </summary>
			/// <details>
			/// 実行順の関係で T → U の順で呼ばなければならない
			/// </details>
			/// <param name="t"></param>
			/// <param name="u"></param>
			/// <returns></returns>
			[[nodiscard]] static uint64_t mix(std::uint64_t t, std::uint64_t u) {

				// Tをベースにする
				std::uint64_t hash = t;

				// Uを順序付きで混ぜる
				hash ^= u + 0x9E3779B97F4A7C15ull + (hash << 6) + (hash >> 2);

				// 上位32bitと下位32bitを混ぜる
				hash ^= hash >> 32;
				return hash;
			}

			/// <summary>
			/// ID合体可変長引数関数
			/// </summary>
			/// <returns>型から取得したID</returns>
			template<typename T, typename... Args>
			[[nodiscard]] static std::uint32_t mix_id() noexcept {

				std::uint64_t hash = static_cast<std::uint64_t>(get_id::get_type_id<T>());

				// Args... を順番に混ぜる
				((hash = mix(
					hash,
					static_cast<std::uint64_t>(get_id::get_type_id<Args>()))
					), ...);

				// 上位32bitと下位32bitを混ぜる
				hash ^= hash >> 32;

				return static_cast<std::uint32_t>(hash);
			}
		}
	}
}