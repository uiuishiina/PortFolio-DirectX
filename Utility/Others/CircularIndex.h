#pragma once
#include<cassert>

/// <summary>
/// その他名前空間
/// </summary>
namespace others {

	/* ========== 循環インデックスクラス定義 ========== */

	/// <summary>
	/// 循環インデックスクラス
	/// </summary>
	class CircularIndex
	{
	public:
		/* ===== メンバー関数 ===== */

		//	通常コンストラクタ削除
		CircularIndex() = delete;

		/// <summary>
		/// 引数付きコンストラクタ
		/// </summary>
		/// <param name="size">インデックスサイズ</param>
		CircularIndex(size_t size) :
			circle_size{ size } {
			assert(circle_size > 0 && "circle_size Error");
		}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~CircularIndex() = default;

		/// <summary>
		/// 前置インクリメントオペレーター
		/// </summary>
		/// <returns>インクリメントした後の自身の参照</returns>
		CircularIndex& operator++() noexcept {
			
			++circle_index;
			circle_index = circle_index % circle_size;
			
			return *this;
		}

		/// <summary>
		/// 前置デクリメントオペレーター
		/// </summary>
		/// <returns>デクリメントした後の自身の参照</returns>
		CircularIndex& operator--() noexcept {

			if (circle_index == 0) {
				circle_index = circle_size - 1;
			}
			else {
				--circle_index;
			}

			return *this;
		}

		/// <summary>
		/// 後置インクリメントオペレーター
		/// </summary>
		/// <returns>インクリメントする前の自身の参照</returns>
		CircularIndex operator++(int) noexcept {
			auto old = *this;
			++(*this);
			return old;
		}

		/// <summary>
		/// 後置デンクリメントオペレーター
		/// </summary>
		/// <returns>デンクリメントする前の自身の参照</returns>
		CircularIndex operator--(int) noexcept {
			auto old = *this;
			--(*this);
			return old;
		}
		
		/// <summary>
		/// インデックス取得オペレーター
		/// </summary>
		/// <returns>インデックス</returns>
		operator size_t()const noexcept {
			return circle_index;
		}

	private:
		/* ===== メンバー変数 ===== */

		/// <summary>
		/// 循環する長さ
		/// </summary>
		const size_t circle_size{};

		/// <summary>
		/// 循環させるインデックス
		/// </summary>
		size_t circle_index{};

	};
}