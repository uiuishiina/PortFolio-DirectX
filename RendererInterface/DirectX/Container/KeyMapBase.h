#pragma once
#include"Others/NonCopyableBase.h"
#include"Container/KeyMap.h"
#include"Key/FeistelKeyConverter.h"

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// コンテナ名前空間
		///====================================================================

		namespace container {

			/// <summary>
			/// 汎用キーハッシュ利用マップ保存基底クラス
			/// </summary>
			/// <typeparam name="Key">倫理側キーの型</typeparam>
			/// <typeparam name="EncodedKey">エンコードされた保存用キーの型</typeparam>
			/// <typeparam name="Handle">保存したデータを取り扱うハンドルの型</typeparam>
			/// <typeparam name="Value">保存するデータ型</typeparam>
			/// <typeparam name="Converter">キーを変換するクラス型</typeparam>
			template<
				typename Key,
				typename EncodedKey,
				typename Handle,
				typename Value,
				typename Converter =  key::FeistelKeyConverter<Key,EncodedKey>
			>
				requires key::concepts::KeyConverter<Converter, Key, EncodedKey>
			class KeyMapBase : others::NonCopyableBase
			{
			public:
				/* ===== メンバー関数 ===== */

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~KeyMapBase() = default;


				/* ===== 取得関数 ===== */

				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="key">取得したいデータに紐づいた倫理側キー</param>
				/// <returns>ハンドル</returns>
				[[nodiscard]] virtual Handle get_handle(const Key& key) noexcept = 0;
				[[nodiscard]] virtual const Handle get_handle(const Key& key) const noexcept = 0;

				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="encode_key">取得したいデータに紐づいた保存用キー</param>
				/// <returns>ハンドル</returns>
				[[nodiscard]] virtual Handle get_handle(const EncodedKey& encode_key) noexcept = 0;
				[[nodiscard]] virtual const Handle get_handle(const EncodedKey& encode_key) const noexcept = 0;


			protected:
				/* ===== メンバー関数 ===== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				KeyMapBase() = default;
				
				/// <summary>
				/// データ追加関数
				/// </summary>
				/// <param name="key">追加したい倫理側のキー</param>
				/// <param name="value">追加したい値</param>
				/// <returns>追加の成否</returns>
				[[nodiscard]] bool add_value(const Key& key, Value&& value) noexcept {
					return map_.add_value(key, std::move(value));
				}


				/* ===== 通常取得側 ===== */

				/// <summary>
				/// データ取得関数
				/// </summary>
				/// <param name="key">探索するキー</param>
				/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
				[[nodiscard]] std::optional<Value> get_value(const Key& key) noexcept {
					return map_.get_value(key);
				}

				[[nodiscard]] const std::optional<Value> get_value(const Key& key) const noexcept {
					return map_.get_value(key);
				}

				/// <summary>
				/// データ取得関数
				/// </summary>
				/// <param name="encode_key">エンコードされた探索するキー</param>
				/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
				[[nodiscard]] std::optional<Value> get_value(const EncodedKey& encode_key) noexcept {
					return map_.get_value(encode_key);
				}

				[[nodiscard]] const std::optional<Value> get_value(const EncodedKey& encode_key) const noexcept {
					return map_.get_value(encode_key);
				}

				/* ===== 保存キー側 ===== */

				/// <summary>
				/// データ取得関数
				/// </summary>
				/// <param name="key">探索するキー</param>
				/// <returns>取得した値のポインター</returns>
				[[nodiscard]] Value* get_value_p(const Key& key) noexcept {

					return map_.get_value_p(key);
				}

				[[nodiscard]] const Value* get_value_p(const Key& key) const noexcept {

					return map_.get_value_p(key);
				}

				/// <summary>
				/// データ取得関数
				/// </summary>
				/// <param name="key">探索するキー</param>
				/// <returns>取得した値のポインター</returns>
				[[nodiscard]] Value* get_value_p(const EncodedKey& encode_key) noexcept {

					return map_.get_value_p(encode_key);
				}

				[[nodiscard]] const Value* get_value_p(const EncodedKey& encode_key) const noexcept {

					return map_.get_value_p(encode_key);
				}


				/* ===== その他 ===== */

				/// <summary>
				/// エンコード関数
				/// </summary>
				/// <param name="key">エンコードしたいキー</param>
				/// <returns>エンコードされたキー</returns>
				[[nodiscard]] EncodedKey encode_key(const Key& key)const noexcept {
					return map_.encode_key(key);
				}

			private:
				/* ===== メンバー変数 ===== */

				/// <summary>
				/// 利用するマップクラス
				/// </summary>
				HandyItems::container::KeyMap<Key, EncodedKey, Value, Converter> map_{};

			};
		}
	}
}