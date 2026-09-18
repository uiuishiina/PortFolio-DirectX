#pragma once
#include"MathF.h"
#include"../BaseStruct/Float3.h"

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItem {

	/// <summary>
	/// 数学名前空間
	/// </summary>
	namespace Math {

		/// <summary>
		/// 数学関数名前空間
		/// </summary>
		namespace MathF {

			/* ========== ベクトル数学 ========== */

			/// <summary>
			/// 内積計算関数
			/// </summary>
			/// <param name="left">左辺値</param>
			/// <param name="right">右辺値</param>
			/// <returns>計算結果</returns>
			[[nodiscard]] inline float dot(
				const Float3& left,
				const Float3& right
			) {
				return
					left.x_ * right.x_ +
					left.y_ * right.y_ +
					left.z_ * right.z_;
			}

			/// <summary>
			/// 外積計算関数
			/// </summary>
			/// <param name="left">左辺値</param>
			/// <param name="right">右辺値</param>
			/// <returns>外積結果</returns>
			[[nodiscard]] inline Float3 cross(
				const Float3& left,
				const Float3& right
			) {
				return {
					left.y_ * right.z_ - left.z_ * right.y_,
					left.z_ * right.x_ - left.x_ * right.z_,
					left.x_ * right.y_ - left.y_ * right.x_
				};
			}

			/// <summary>
			/// 距離二乗計算関数
			/// </summary>
			/// <param name="left">左辺値</param>
			/// <param name="right">右辺値</param>
			/// <returns>計算結果</returns>
			[[nodiscard]] inline float distance_squared(
				const Float3& left,
				const Float3& right
			) {

				const auto x_len = left.x_ - right.x_;
				const auto y_len = left.y_ - right.y_;
				const auto z_len = left.z_ - right.z_;

				return
					x_len * x_len +
					y_len * y_len +
					z_len * z_len;
			}

			/// <summary>
			/// 距離計算関数
			/// </summary>
			/// <param name="left">左辺値</param>
			/// <param name="right">右辺値</param>
			/// <returns>計算結果</returns>
			[[nodiscard]] inline float distance(
				const Float3& left,
				const Float3& right
			) {

				//	距離の二乗を平方根
				return MathF::sqrt(distance_squared(left, right));
			}

		}
	}
}