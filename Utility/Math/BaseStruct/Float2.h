#pragma once
#include"../Function/MathF.h"
#include<cassert>

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItem {

	/// <summary>
	/// 数学名前空間
	/// </summary>
	namespace Math {

		/// <summary>
		/// 二次元浮動小数点構造体
		/// </summary>
		/// <details>
		/// [ X ][ Y ] の値を持つ 2 次元浮動小数点構造体
		/// </details>
		struct Float2 {

			/* ========== メンバー変数 ========== */

			/// <summary>
			/// [ X ] の値
			/// </summary>
			float x_{};

			/// <summary>
			/// [ Y ] の値
			/// </summary>
			float y_{};

			/* ========== メンバー関数 ========== */

			/* -- 設定 -- */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			Float2() = default;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="x">[ X ] の値</param>
			/// <param name="y">[ Y ] の値</param>
			Float2(
				float x,
				float y
			) :
				x_{ x },
				y_{ y } {}


			/* ========== 演算子オーバーロード ========== */

			/* ===== アクセス ===== */

			/// <summary>
			/// 要素アクセス演算子
			/// </summary>
			/// <param name="index">要素番号（0: X、1: Y）</param>
			/// <returns>指定した要素への参照</returns>
			[[nodiscard]] float& operator [] (
				std::size_t index
				) {

				assert(index < 2 && "Float2 index out of range");
				return 0 == index ? x_ : y_;
			}

			/// <summary>
			/// 要素アクセス演算子
			/// </summary>
			/// <param name="index">要素番号（0: X、1: Y）</param>
			/// <returns>指定した要素へのConst参照</returns>
			[[nodiscard]] const float& operator [] (
				std::size_t index
				) const {

				assert(index < 2 && "Float2 index out of range");
				return 0 == index ? x_ : y_;
			}

			/* ===== 加算 ===== */

			/// <summary>
			/// 加算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>加算結果</returns>
			[[nodiscard]] Float2 operator + (
				const Float2& right
				) const {

				return {
					x_ + right.x_,
					y_ + right.y_
				};
			}

			/// <summary>
			/// 加算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>加算後の自身参照</returns>
			Float2& operator += (
				const Float2& right
				) {

				*this = *this + right;

				return *this;
			}


			/* ===== 減算 ===== */

			/// <summary>
			/// 減算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>減算結果</returns>
			[[nodiscard]] Float2 operator - (
				const Float2& right
				) const {

				return { 
					x_ - right.x_,
					y_ - right.y_ 
				};
			}

			/// <summary>
			/// 減算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>減算後の自身参照</returns>
			Float2& operator -= (
				const Float2& right
				) {

				*this = *this - right;

				return *this;
			}


			/* ===== 乗算 ===== */

			/// <summary>
			/// 乗算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>乗算結果</returns>
			[[nodiscard]] Float2 operator * (
				const Float2& right
				) const {

				return {
					x_ * right.x_,
					y_ * right.y_
				};
			}

			/// <summary>
			/// 乗算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>乗算後の自身参照</returns>
			Float2& operator *= (
				const Float2& right
				) {

				*this = *this * right;

				return *this;
			}

			/// <summary>
			/// スカラー倍乗算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>乗算結果</returns>
			[[nodiscard]] Float2 operator * (
				float right
				) const {

				return {
					x_ * right,
					y_ * right
				};
			}

			/// <summary>
			/// スカラー倍乗算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>乗算後の自身参照</returns>
			Float2& operator *= (
				float right
				) {

				*this = *this * right;

				return *this;
			}


			/* ===== 除算 ===== */

			/// <summary>
			/// 除算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>除算結果</returns>
			[[nodiscard]] Float2 operator / (
				const Float2& right
				) const {

				return {
					x_ / right.x_,
					y_ / right.y_
				};
			}

			/// <summary>
			/// 除算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>除算後の自身参照</returns>
			Float2& operator /= (
				const Float2& right
				) {

				*this = *this / right;

				return *this;
			}

			/// <summary>
			/// スカラー倍除算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>除算結果</returns>
			[[nodiscard]] Float2 operator / (
				float right
				) const {

				return {
					x_ / right,
					y_ / right
				};
			}

			/// <summary>
			/// スカラー倍除算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>除算後の自身参照</returns>
			Float2& operator /= (
				float right
				) {

				*this = *this / right;

				return *this;
			}
			

			/* ===== 比較 ===== */

			/// <summary>
			/// 等値比較演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>比較結果</returns>
			[[nodiscard]] bool operator == (
				const Float2& right
				) const {

				return (
					x_ == right.x_ && 
					y_ == right.y_
					);
			}

			/// <summary>
			/// 非等値比較演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>比較結果</returns>
			[[nodiscard]] bool operator != (
				const Float2& right
				) const {

				return !(*this == right);
			}
			

			/* ===== その他 ===== */

			/// <summary>
			/// 符号反転演算子
			/// </summary>
			/// <returns></returns>
			Float2 operator - () const {

				return {
					-x_,
					-y_
				};
			}


			/* ===== 数学系関数 ===== */

			/// <summary>
			/// 二乗距離計算関数
			/// </summary>
			/// <returns>距離の二乗</returns>
			[[nodiscard]] float length_squared() const {

				return (
					x_ * x_ +
					y_ * y_
					);
			}

			/// <summary>
			/// 距離計算関数
			/// </summary>
			/// <returns>距離</returns>
			[[nodiscard]] float length() const {

				return MathF::sqrt(length_squared());
			}

			/// <summary>
			/// 正規化関数
			/// </summary>
			/// <returns>正規化後の自身参照</returns>
			Float2& normalize() {

				const auto length = this->length();

				if (length != 0.0f) {
					*this /= length;
				}

				return *this;
			}

			/// <summary>
			/// 正規化取得関数
			/// </summary>
			/// <returns>正規化された値</returns>
			[[nodiscard]] Float2 normalized() const {

				const auto length = this->length();

				if (length != 0.0f) {
					return *this / length;
				}

				return *this;
			}

		};
	}
}