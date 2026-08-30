#pragma once
#include<queue>
#include<optional>
#include<functional>

/// <summary>
/// 便利用名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// コンテナ用名前空間
	/// </summary>
	namespace container {

		/* ========== 参照保存キュークラス定義 ========== */

		/// <summary>
		/// 参照保存キュークラス
		/// </summary>
		/// <typeparam name="T">キューに保存したい型</typeparam>
		template<typename T>
		class ReferenceQueue
		{
		public:
			/* ===== メンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ReferenceQueue() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~ReferenceQueue() = default;

			/// <summary>
			/// 参照追加関数
			/// </summary>
			/// <param name="value">追加する参照</param>
			void add_reference(T& value) {
				reference_queue.push(value);
			}

			/// <summary>
			/// 参照配列追加関数
			/// </summary>
			/// <typeparam name="R"></typeparam>
			/// <param name="value"></param>
			template<std::ranges::range R>
			requires std::same_as<std::remove_cvref_t<std::ranges::range_reference_t<R>>, T>
			void add_references(R& value) {
				for (auto& p : value) {
					reference_queue.push(p);
				}
			}

			/// <summary>
			/// 参照取得関数
			/// </summary>
			/// <returns>キューから取得した参照...ないなら[std::nullopt]</returns>
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_reference() {

				//	キューがあるか
				if (reference_queue.empty()) {
					return std::nullopt;
				}

				auto value = reference_queue.front();
				reference_queue.pop();

				return value;
			}

		private:
			/* ===== メンバー関数 ===== */

			/// <summary>
			/// 参照保存キュー
			/// </summary>
			std::queue<std::reference_wrapper<T>> reference_queue{};
		};
	}
}