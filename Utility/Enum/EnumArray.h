#pragma once
#include"EnumToIndex.h"
#include<array>
#include<cassert>

/// <summary>
/// 便利用名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// 列挙体名前空間
	/// </summary>
	namespace Enum {

		/// <summary>
		/// 列挙体対応配列構造体
		/// </summary>
		/// <typeparam name="Value">保存する値</typeparam>
		/// <typeparam name="Enum">配列に利用する列挙体... [ 要素にCountがある事が条件 ]</typeparam>
		template<concepts::EnumHasCount Enum, typename Value>
		struct EnumArray {

			/* ===== メンバー変数 ===== */

			/// <summary>
			/// 保存配列
			/// </summary>
			std::array<Value, enum_to_index(Enum::Count)> array_{};

			/* ===== メンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			EnumArray() {
				static_assert(enum_to_index(Enum::Count) > 0, "EnumArray must have at least one element");
			}

			/// <summary>
			/// 変更可能アクセスオペレーター
			/// </summary>
			/// <param name="value">アクセスしたい列挙体の要素</param>
			/// <returns>要素に対応した配列参照</returns>
			Value& operator[](Enum value) {
				assert(value != Enum::Count && "EnumArray use Count");
				return array_[enum_to_index(value)];
			}

			/// <summary>
			/// 変更不能アクセスオペレーター
			/// </summary>
			/// <param name="value">アクセスしたい列挙体の要素</param>
			/// <returns>要素に対応した配列参照</returns>
			const Value& operator[](Enum value) const {
				assert(value != Enum::Count && "EnumArray use Count");
				return array_[enum_to_index(value)];
			}

			/// <summary>
			/// 配列サイズ取得関数
			/// </summary>
			/// <returns>配列サイズ</returns>
			constexpr std::size_t size()const noexcept {
				return array_.size();
			}


			/// <details>
			/// 範囲アクセス補助関数群
			/// </details>

			auto begin() noexcept { return array_.begin(); }
			auto end() noexcept { return array_.end(); }

			auto begin() const noexcept { return array_.begin(); }
			auto end() const noexcept { return array_.end(); }

			auto cbegin() const noexcept { return array_.cbegin(); }
			auto cend() const noexcept { return array_.cend(); }

		};
	}
}