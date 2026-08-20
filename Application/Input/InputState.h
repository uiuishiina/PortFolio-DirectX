#pragma once
#include"EnumToIndex.h"
#include<bitset>
#include<concepts>

///====================================================================
/// テンプレートコンセプト名前空間
///====================================================================

namespace concepts {

	template<typename T>
	concept Enum_has_Count = std::is_enum_v<T> && requires {
		static_cast<size_t>(T::Count);
	};
};

///====================================================================
/// 入力名前空間
///====================================================================

namespace input {

	///====================================================================
	/// InputState 構造体
	///====================================================================

	//@brief	=== 入力状態構造体 ===
	template<concepts::Enum_has_Count T>
	struct InputState
	{
		///====================================================================
		/// メンバー変数
		///====================================================================

		//@brief	== キー状態保存変数 ==
		std::bitset<to_index(T::Count)> key_{};

		///====================================================================
		/// メンバー関数
		///====================================================================

		/* -- 設定関数 -- */

		//@brief	=== キー状態セット関数 ===
		//@param	key		セットするキー
		//@param	value	セットする値
		void set_key(T key, bool value) {

			key_.set(to_index(key), value);
		}

		//@broef	=== キー状態配列セット関数 ===
		//@param	value	セットするキー配列
		void set_keys(const std::bitset<to_index(T::Count)>& value) {

			key_ = value;
		}

		//@broef	=== キー状態配列ビットセット関数 ===
		//@param	value	セットするビット
		//@param	start	セットするキー配列の先頭要素
		//@param	size	セットするキー配列のインデックスからの長さ
		void set_bits(uint64_t value, T start, size_t count) {

			// 先頭インデックス取得
			const auto begin = to_index(start);

			//	先頭インデックスより後をセット
			for (size_t i = 0; i < count; ++i) {
				key_.set(begin + i, (value >> i) & 1ULL);
			}
		}


		/* -- 取得関数 -- */

		//@brief	=== キー状態取得関数 ===
		//@param	key	取得するキー
		//@return	キー状態
		[[nodiscard]] bool get_key(T key)const noexcept {

			return key_.test(to_index(key));
		}

	};
};