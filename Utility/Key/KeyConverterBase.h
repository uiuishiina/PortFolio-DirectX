#pragma once
#include"../ID/IDBase.h"
#include<concepts>
#include"../../Debug/DebugLogSystem.h"

/// <summary>
/// キー名前空間
/// </summary>
namespace key {

	/// <summary>
	/// 初期設定値キー
	/// </summary>
	struct DefaultKey {

		/* ===== メンバー変数 ===== */

		/// <summary>
		/// キー保存変数
		/// </summary>
		std::uint32_t key_value{};

		/* ===== メンバー関数 ===== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DefaultKey() = default;

		/// <summary>
		/// 引数付きコンストラクタ
		/// </summary>
		/// <param name="value">キーに入れる値</param>
		DefaultKey(std::uint32_t value) :
			key_value{ value } {}

	};

	/* ========== テンプレートコンセプト定義 ========== */

	/// <summary>
	/// テンプレートコンセプト定義用名前空間
	/// </summary>
	namespace concepts {

		/// <summary>
		/// キー指定コンセプト
		/// </summary>
		/// <details>
		/// [ key_value ] というメンバー変数があり
		///	それが[std::uint32_t] であることを保証する
		/// </details>
		template<typename T>
		concept HasKeyValue = requires(const T & value) {
			value.key_value;
		} && std::same_as<decltype(T::key_value),std::uint32_t>;

	}

	/* ========== キー変換基底クラス定義 ========== */

	/// <summary>
	/// キー変換基底クラス
	/// </summary>
	/// <details>
	/// [ 変換する型 ] の制約を示す, [ 可逆性とアルゴリズム ] は派生で示す
	/// </details>
	/// <typeparam name="T">エンコードするキー</typeparam>
	/// <typeparam name="U">デコードするキー</typeparam>
	template<concepts::HasKeyValue T = DefaultKey, concepts::HasKeyValue U = DefaultKey>
	class KeyConverterBase
	{
	public:
		/* ===== メンバー関数 ===== */

		//	通常コンストラクタ削除
		KeyConverterBase() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~KeyConverterBase() = default;

		/// <summary>
		/// エンコード関数
		/// </summary>
		/// <param name="value">エンコードしたいキー</param>
		/// <returns>エンコードされたキー</returns>
		[[nodiscard]] virtual U encode_key(const T& value) const = 0;

		/// <summary>
		/// デコード関数
		/// </summary>
		/// <param name="value">デコードしたいキー</param>
		/// <returns>デコードされたキー</returns>
		[[nodiscard]] virtual  T decode_key(const U& value) const = 0;

	protected:
		/* ===== メンバー変数 ===== */

		/// <summary>
		/// 変換定数
		/// </summary>
		const std::uint32_t conversion_constant = HandyItems::id::make_id::mix_id<T, U>();

	};


	/* ========== テンプレートコンセプト定義 ========== */

	/// <summary>
	/// テンプレートコンセプト定義用名前空間
	/// </summary>
	namespace concepts {

		/// <summary>
		/// キー変換指定コンセプト
		/// </summary>
		/// <details>
		/// KeyConverterBase の宣言後に定義する必要があるため、ここで定義
		/// </details>
		/// <typeparam name="Converter">キー変換派生クラス</typeparam>
		/// <typeparam name="Encode">エンコードするキー</typeparam>
		/// <typeparam name="Decode">デコードするキー</typeparam>
		template<typename Converter, typename Encode, typename Decode>
		concept KeyConverter =
			std::derived_from<
			Converter,
			KeyConverterBase<Encode, Decode>
			>;
	}
}