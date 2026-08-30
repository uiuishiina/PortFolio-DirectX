#pragma once
#include<unordered_map>
#include<optional>

/// <summary>
/// 便利用名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// コンテナ用名前空間
	/// </summary>
	namespace container {

		/* ========== 重複なしコンテナクラス定義 ========== */

		/// <summary>
		/// 重複なしコンテナクラス
		/// </summary>
		/// <typeparam name="Key">キーにする型</typeparam>
		/// <typeparam name="Value">保存する型</typeparam>
		template<typename Key, typename Value>
		class UnorderedMapBase
		{
		public:
			/* ===== メンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			UnorderedMapBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~UnorderedMapBase() = default;

			/// <summary>
			/// コンテナ追加関数
			/// </summary>
			/// <param name="key">登録するキー</param>
			/// <param name="value">追加する値</param>
			/// <returns>追加の成否</returns>
			bool add_value(const Key& key, const Value& value) {
				return map_.emplace(key, value).second;
			}

			/// <summary>
			/// コンテナ取得関数
			/// </summary>
			/// <param name="key">探索するキー</param>
			/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Value> get_value(const Key& key) const noexcept {

				const auto it = map_.find(key);
				if (it == map_.end()) {
					return std::nullopt;
				}

				return it->second;
			}

		protected:
			/* ===== メンバー関数 ===== */

			/// <summary>
			/// 変更可能コンテナ本体取得関数
			/// </summary>
			/// <returns>変更可能なコンテナ参照</returns>
			[[nodiscard]] auto& get_map() noexcept {
				return map_;
			}

			/// <summary>
			/// 変更不可能コンテナ本体取得関数
			/// </summary>
			/// <returns>変更不可能なコンテナ参照</returns>
			[[nodiscard]] const auto& get_map() const noexcept {
				return map_;
			}

		private:
			/* ===== メンバー変数 ===== */

			/// <summary>
			/// マップコンテナ本体
			/// </summary>
			std::unordered_map<Key, Value> map_{};

		};
	}
}