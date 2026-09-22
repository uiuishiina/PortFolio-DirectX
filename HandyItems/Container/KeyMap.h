#pragma once
#include"UnorderedMapBase.h"
#include"../Key/KeyConverterBase.h"

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// コンテナ用名前空間
	/// </summary>
	namespace container {

		/// <summary>
		/// ハンドル名前空間
		/// </summary>
		namespace handle {

			/* ========== 汎用基底キー定義 ========== */

			/// <summary>
			/// 倫理側基底キー
			/// </summary>
			struct LogicalKey : public key::DefaultKey {

				/// <summary>
				/// コンストラクタ
				/// </summary>
				LogicalKey() = default;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="key">キーに入れる値</param>
				LogicalKey(
					std::uint32_t key
				) :
					DefaultKey(key) {}

			};

			/// <summary>
			/// 保存側基底キー
			/// </summary>
			struct EncodedKey : public key::DefaultKey {

				/// <summary>
				/// コンストラクタ
				/// </summary>
				EncodedKey() = default;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="key">キーに入れる値</param>
				EncodedKey(
					std::uint32_t key
				) :
					DefaultKey(key) {}

			};


			/* ========== 汎用基底ハンドル定義 ========== */

			/// <summary>
			/// ハンドル基底構造体
			/// </summary>
			/// <typeparam name="T">保存している型</typeparam>
			/// <typeparam name="Key">保存側派生キーの型</typeparam>
			template<typename T, typename Key>
				requires std::derived_from<Key, EncodedKey>
			struct HandleBase {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// ハンドル本体
				/// </summary>
				T handle_{};

				/// <summary>
				/// ハンドル識別キー
				/// </summary>
				Key handle_key{};

			};

			/// <summary>
			/// ポインターハンドル基底構造体
			/// </summary>
			/// <typeparam name="T">保存している型</typeparam>
			/// <typeparam name="Key">保存側派生キーの型</typeparam>
			template<typename T, typename Key>
				requires std::derived_from<Key, EncodedKey>
			struct HandlePtrBase {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// ハンドル本体
				/// </summary>
				T* handle_p{};

				/// <summary>
				/// ハンドル識別キー
				/// </summary>
				Key handle_key{};

			};

		}


		/* ========== キーマップコンテナクラス定義 ========== */

		/// <summary>
		/// キーマップコンテナクラス
		/// </summary>
		/// <details>
		/// ハッシュにキー変換を利用するクラス
		/// </details>
		/// <typeparam name="LogicalKeyT">倫理側派生キー</typeparam>
		/// <typeparam name="Decode">保存側派生キー</typeparam>
		/// <typeparam name="Value">保存する型</typeparam>
		/// <typeparam name="Converter">キー変換派生クラス</typeparam>
		template<
			typename LogicalKeyT,
			typename EncodedKeyT,
			typename Value,
			typename Converter
		>
		requires 
			std::derived_from<LogicalKeyT,handle::LogicalKey> &&
			std::derived_from<EncodedKeyT,handle::EncodedKey> &&
			key::concepts::KeyConverter<Converter, LogicalKeyT, EncodedKeyT>
		class KeyMap
		{
		public:
			/* ========== メンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			KeyMap() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~KeyMap() = default;


			/* ========== 追加関数 ========== */

			/// <summary>
			/// 値追加関数
			/// </summary>
			/// <param name="key">登録するキー</param>
			/// <param name="value">追加する値</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_value(
				const LogicalKeyT& key, 
				Value&& value
			) {

				return map_.add_value(encode_key(key).key_value, std::move(value));
			}


			/* ========== 取得関数 ========== */

			/* ===== 参照 ===== */

			/// <summary>
			/// 値取得関数
			/// </summary>
			/// <param name="encode_key">エンコードされたキー</param>
			/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Value> get_value(
				const EncodedKeyT& encodekey
			) noexcept {

				return map_.get_value(encodekey.key_value);
			}

			[[nodiscard]] std::optional<Value> get_value(
				const EncodedKeyT& encodekey
			) const noexcept {

				return map_.get_value(encodekey.key_value);
			}

			/// <summary>
			/// 値取得オーバーロード関数
			/// </summary>
			/// <param name="key">エンコードするキー</param>
			/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Value> get_value(
				const LogicalKeyT& key
			) noexcept {

				return map_.get_value(encode_key(key).key_value);
			}

			[[nodiscard]] const std::optional<Value> get_value(
				const LogicalKeyT& key
			) const noexcept {

				return map_.get_value(encode_key(key).key_value);
			}


			/* ===== ポインター ===== */

			/// <summary>
			/// 値ポインター取得関数
			/// </summary>
			/// <param name="key">探索するキー</param>
			/// <returns>取得した値... ないなら [ nullptr ]</returns>
			[[nodiscard]] Value* get_value_p(
				const EncodedKeyT& encodekey
			) noexcept {

				return map_.get_value_p(encodekey.key_value);
			}

			[[nodiscard]] const Value* get_value_p(
				const EncodedKeyT& encodekey
			) const noexcept {

				return map_.get_value_p(encodekey.key_value);
			}

			/// <summary>
			/// 値ポインター取得関数
			/// </summary>
			/// <param name="key">探索するキー</param>
			/// <returns>取得した値... ないなら [ nullptr ]</returns>
			[[nodiscard]] Value* get_value_p(
				const LogicalKeyT& key
			) noexcept {

				return map_.get_value_p(encode_key(key).key_value);
			}

			[[nodiscard]] const Value* get_value_p(
				const LogicalKeyT& key
			) const noexcept {

				return map_.get_value_p(encode_key(key).key_value);
			}


			/* ===== その他 ===== */

			/// <summary>
			/// エンコード関数
			/// </summary>
			/// <param name="key">エンコードしたいキー</param>
			/// <returns>エンコードされたキー</returns>
			[[nodiscard]] EncodedKeyT encode_key(
				const LogicalKeyT& key
			) const noexcept {

				return converter_.encode_key(key);
			}

			/// <summary>
			/// デコード関数
			/// </summary>
			/// <param name="encode_key">デコードしたいキー</param>
			/// <returns>デコードされたキー</returns>
			[[nodiscard]] LogicalKeyT decode_key(
				const EncodedKeyT& encodekey
			) const noexcept {

				return converter_.decode_key(encodekey);
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