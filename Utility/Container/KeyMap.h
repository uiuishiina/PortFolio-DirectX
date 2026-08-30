#pragma once
#include"UnorderedMapBase.h"
#include"../Key/KeyConverterBase.h"

/// <summary>
/// 便利用名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// コンテナ用名前空間
	/// </summary>
	namespace container {

		/// <summary>
		/// 重複なしキー変換保存クラス
		/// </summary>
		/// <details>
		/// ハッシュにキー変換を利用するクラス
		/// </details>
		/// <typeparam name="Encode">エンコードするキー</typeparam>
		/// <typeparam name="Decode">エンコードされたキー</typeparam>
		/// <typeparam name="Value">保存する型</typeparam>
		/// <typeparam name="Converter">キー変換派生クラス</typeparam>
		template<
			typename Key,
			typename EncodedKey,
			typename Value,
			typename Converter
		>
			requires key::concepts::KeyConverter<Converter, Key, EncodedKey>
		class KeyMap
		{
		public:
			/* ===== メンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			KeyMap() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~KeyMap() = default;

			/// <summary>
			/// コンテナ追加関数
			/// </summary>
			/// <param name="key">登録するキー</param>
			/// <param name="value">追加する値</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_value(const Key& key, const Value& value) {

				return map_.add_value(encode_key(key).key_value, std::move(value));
			}

			/// <summary>
			/// コンテナ取得関数
			/// </summary>
			/// <param name="key">探索するキー</param>
			/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Value> get_value(const Key& key) const noexcept {

				return map_.get_value(encode_key(key).key_value);
			}

			/// <summary>
			/// コンテナ取得オーバーロード関数
			/// </summary>
			/// <param name="encode_key">エンコードされたキー</param>
			/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Value> get_value(const EncodedKey& encode_key) const noexcept {

				return map_.get_value(encode_key.key_value);
			}

			/// <summary>
			/// エンコード関数
			/// </summary>
			/// <param name="key">エンコードしたいキー</param>
			/// <returns>エンコードされたキー</returns>
			[[nodiscard]] EncodedKey encode_key(const Key& key)const noexcept {

				return converter_.encode_key(key);
			}

			/// <summary>
			/// デコード関数
			/// </summary>
			/// <param name="encode_key">デコードしたいキー</param>
			/// <returns>デコードされたキー</returns>
			[[nodiscard]] Key decode_key(const Key& encode_key)const noexcept {

				return converter_.decode_key(encode_key);
			}

		private:
			/* ===== メンバー変数 ===== */

			/// <summary>
			/// 保存するマップ
			/// </summary>
			UnorderedMapBase<std::uint32_t, Value> map_{};

			/// <summary>
			/// キー変換クラス
			/// </summary>
			Converter converter_{};

		};
	}
}