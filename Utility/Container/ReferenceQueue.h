#pragma once
#include"ReferenceContainerBase.h"
#include<queue>

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
		class ReferenceQueue : public ReferenceContainerBase<T>
		{
		public:
			/* =============== クラス設定 =============== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ReferenceQueue() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~ReferenceQueue() = default;


			/* =============== 追加関数 =============== */

			/// <summary>
			/// 参照追加関数
			/// </summary>
			/// <param name="value">追加する参照</param>
			void add_reference(T& value) override {
				reference_queue.push(value);
			}


			/* =============== 取得関数 =============== */

			/// <summary>
			/// 前方参照取得関数
			/// </summary>
			/// <returns>取得した参照...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_front_reference() override {

				//	キューがあるか
				if (reference_queue.empty()) {
					return std::nullopt;
				}

				auto value = reference_queue.front();
				reference_queue.pop();

				return value;
			}

		private:
			/* =============== メンバー変数 =============== */

			/// <summary>
			/// 参照保存キュー
			/// </summary>
			std::queue<std::reference_wrapper<T>> reference_queue{};


			/* =============== メンバー関数 =============== */

			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_front_reference() const override { return std::nullopt; };
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_back_reference() override { return std::nullopt; };
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_back_reference() const override { return std::nullopt; };
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_reference_to_index(std::size_t index) override { return std::nullopt; };
			[[nodiscard]] std::optional<std::reference_wrapper<T>> get_reference_to_index(std::size_t index) const override { return std::nullopt; };
		};
	}
}