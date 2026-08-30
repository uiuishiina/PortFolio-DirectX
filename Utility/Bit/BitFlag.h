#pragma once
#include"../Enum/EnumToIndex.h"
#include<bitset>

/// <summary>
/// ビット名前空間
/// </summary>
namespace bit {

	/* ========== ビットフラグクラス定義 ========== */

	/// <summary>
	/// ビットフラグクラス
	/// </summary>
	/// <typeparam name="T">Bitフラグに使う列挙体の型</typeparam>
	template<Enum::concepts::EnumHasCount T>
	class BitFlag 
	{
	public:
		/* ===== メンバー関数 ===== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		BitFlag() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~BitFlag() = default;
		
		/// <summary>
		/// ビットセット関数
		/// </summary>
		/// <param name="value">対応するenum</param>
		void set(T value) {
			bit_.set(others::enum_to_index(value));
		}

		/// <summary>
		/// ビットリセット関数
		/// </summary>
		/// <param name="value">対応するenum</param>
		void reset(T value) {
			bit_.reset(others::enum_to_index(value));
		}

		/// <summary>
		/// ビットクリア関数
		/// </summary>
		void clear() {
			bit_.reset();
		}

		/// <summary>
		/// ビットテスト関数
		/// </summary>
		/// <param name="value">対応するenum</param>
		/// <returns>テスト結果</returns>
		[[nodiscard]] bool test(T value) const {
			return bit_.test(others::enum_to_index(value));
		}

		/// <summary>
		/// [ true ] ビット存在判定関数
		/// </summary>
		/// <returns> 一つでもビットが立っていたら [ true ] </returns>
		[[nodiscard]] bool any() const {
			return bit_.any();
		}

		/// <summary>
		/// 全ビット [ false ] 判定関数
		/// </summary>
		/// <returns> すべてのビットが立っていないなら [ true ] </returns>
		[[nodisacrd]] bool none() const {
			return bit_.none();
		}

	private:
		/* ===== メンバー変数 ===== */

		/// <summary>
		/// ビットフラグ
		/// </summary>
		std::bitset<others::enum_to_index(T::Count)> bit_;
	};
}