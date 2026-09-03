#pragma once
#include"Enum/EnumToIndex.h"
#include<bitset>
#include<concepts>

/// <summary>
/// 入力名前空間
/// </summary>
namespace input {

	/// <summary>
	/// 入力キー状態構造体
	/// </summary>
	/// <typeparam name="T">キー列挙体</typeparam>
	template<HandyItems::Enum::concepts::EnumHasCount T>
	struct InputState {
		
		/* ========== Publicメンバー変数 ========== */

		/// <summary>
		/// キー状態保存変数
		/// </summary>
		std::bitset<HandyItems::Enum::enum_to_index(T::Count)> key_{};


		/* ========== Publicメンバー関数 ========== */

		/* -- 設定関数 -- */

		/// <summary>
		/// キー状態セット関数
		/// </summary>
		/// <param name="key">対応する列挙体</param>
		/// <param name="value">設定する値</param>
		void set_key(T key, bool value) {

			key_.set(HandyItems::Enum::enum_to_index(key), value);
		}

		/// <summary>
		/// キー状態配列セット関数
		/// </summary>
		/// <param name="value"></param>
		void set_keys(const std::bitset<HandyItems::Enum::enum_to_index(T::Count)>& value) {

			key_ = value;
		}

		/// <summary>
		/// キー状態配列ビットセット関数
		/// </summary>
		/// <param name="value">セットするビット</param>
		/// <param name="start">セットするキー配列の先頭要素</param>
		/// <param name="count">セットするキー配列のインデックスからの長さ</param>
		void set_bits(uint64_t value, T start, size_t count) {

			// 先頭インデックス取得
			const auto begin = HandyItems::Enum::enum_to_index(start);

			//	先頭インデックスより後をセット
			for (size_t i = 0; i < count; ++i) {
				key_.set(begin + i, (value >> i) & 1ULL);
			}
		}


		/* -- 取得関数 -- */

		/// <summary>
		/// キー状態取得関数
		/// </summary>
		/// <param name="key">対応する列挙体</param>
		/// <returns>対応するキー状態</returns>
		[[nodiscard]] bool get_key(T key)const noexcept {

			return key_.test(HandyItems::Enum::enum_to_index(key));
		}

	};
}