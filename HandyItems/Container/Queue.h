#pragma once

#include<queue>
#include<optional>

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// コンテナ用名前空間
	/// </summary>
	namespace container {

		template<typename T>
		class Queue
		{
		public:
			/* ===== メンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			Queue() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~Queue() = default;

			/// <summary>
			/// キュー追加関数
			/// </summary>
			/// <param name="value">追加する値</param>
			void push(T value) {

				queue_.push(value);
			}

			/// <summary>
			/// キュー取得関数
			/// </summary>
			/// <returns>取得した値... ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<T> pop() {

				if (queue_.empty()) {
					return std::nullopt;
				}

				const auto value = queue_.front();
				queue_.pop();

				return value;
			}

			/// <summary>
			/// キュー所持判定関数
			/// </summary>
			/// <returns>キューの中身があるなら [ true ]</returns>
			[[nodiscard]] bool empty()const noexcept {

				return queue_.empty();
			}

			/// <summary>
			/// キューサイズ取得関数
			/// </summary>
			/// <returns>キューサイズ</returns>
			[[nodiscard]] std::size_t size()const noexcept {

				return static_cast<std::size_t>(queue_.size());
			}

			/// <summary>
			/// キュークリア関数
			/// </summary>
			void clear() {
				queue_ = {};
			}

		private:
			/* ===== メンバー変数 ===== */

			/// <summary>
			/// キュー
			/// </summary>
			std::queue<T> queue_{};

		};
	}
}