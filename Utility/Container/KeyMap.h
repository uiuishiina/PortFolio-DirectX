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
			/// データ追加関数
			/// </summary>
			/// <param name="key">登録するキー</param>
			/// <param name="value">追加する値</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_value(const Key& key, Value&& value) {

				return map_.add_value(encode_key(key).key_value, std::move(value));
			}


			/* ===== 通常取得側 ===== */

			/// <summary>
			/// データ取得関数
			/// </summary>
			/// <param name="key">探索するキー</param>
			/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Value> get_value(const Key& key) noexcept {

				return map_.get_value(encode_key(key).key_value);
			}

			[[nodiscard]] const std::optional<Value> get_value(const Key& key)const noexcept {

				return map_.get_value(encode_key(key).key_value);
			}


			/// <summary>
			/// データ取得関数
			/// </summary>
			/// <param name="encode_key">エンコードされた探索するキー</param>
			/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Value> get_value(const EncodedKey& encode_key) noexcept {

				return map_.get_value(encode_key.key_value);
			}

			[[nodiscard]] const std::optional<Value> get_value(const EncodedKey& encode_key) const noexcept {

				return map_.get_value(encode_key.key_value);
			}


			/* ===== ポインター取得側 ===== */

			/// <summary>
			/// データ取得関数
			/// </summary>
			/// <param name="key">探索するキー</param>
			/// <returns>取得した値のポインター</returns>
			[[nodiscard]] Value* get_value_p(const Key& key) noexcept {

				return map_.get_value_p(encode_key(key).key_value);
			}

			[[nodiscard]] const Value* get_value_p(const Key& key) const noexcept {

				return map_.get_value_p(encode_key(key).key_value);
			}

			/// <summary>
			/// データ取得関数
			/// </summary>
			/// <param name="key">探索するキー</param>
			/// <returns>取得した値のポインター</returns>
			[[nodiscard]] Value* get_value_p(const EncodedKey& encode_key) noexcept {

				return map_.get_value_p(encode_key.key_value);
			}

			[[nodiscard]] const Value* get_value_p(const EncodedKey& encode_key) const noexcept {

				return map_.get_value_p(encode_key.key_value);
			}


			/* ===== その他 ===== */

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
			[[nodiscard]] Key decode_key(const EncodedKey& encode_key)const noexcept {

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