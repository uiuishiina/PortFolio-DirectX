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
		/// 四次元浮動小数点構造体
		/// </summary>
		/// <details>
		/// [ X ][ Y ][ Z ][ W ] の値を持つ 4 次元浮動小数点構造体
		/// </details>
		struct Float4 {

			/* ========== メンバー変数 ========== */

			/// <summary>
			/// [ X ] の値
			/// </summary>
			float x_{};

			/// <summary>
			/// [ Y ] の値
			/// </summary>
			float y_{};

			/// <summary>
			/// [ Z ] の値
			/// </summary>
			float z_{};

			/// <summary>
			/// [ W ] の値
			/// </summary>
			float w_{};

			/* ========== メンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			Float4() = default;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="x">[ X ] の値</param>
			/// <param name="y">[ Y ] の値</param>
			/// <param name="z">[ Z ] の値</param>
			/// <param name="w">[ W ] の値</param>
			Float4(
				float x, 
				float y, 
				float z, 
				float w = 1.0f
			) :
				x_{ x },
				y_{ y }, 
				z_{ z }, 
				w_{ w } {}


			/* ========== 演算子オーバーロード ========== */

			/* ===== アクセス ===== */

			/// <summary>
			/// 要素アクセス演算子
			/// </summary>
			/// <param name="index">要素番号（0: X、1: Y、2: Z、3: W）</param>
			/// <returns>指定した要素への参照</returns>
			[[nodiscard]] float& operator []  (
				std::size_t index
				) {

				assert(index < 4 && "Float4 index out of range");
				switch (index)
				{
				case 0:
					return x_;
				case 1:
					return y_;
				case 2:
					return z_;
				default:
					return w_;
				}
			}

			/// <summary>
			/// 要素アクセス演算子
			/// </summary>
			/// <param name="index">要素番号（0: X、1: Y、2: Z、3: W）</param>
			/// <returns>指定した要素へのConst参照</returns>
			[[nodiscard]] const float& operator [] (
				std::size_t index
				) const {

				assert(index < 4 && "Float4 index out of range");
				switch (index)
				{
				case 0:
					return x_;
				case 1:
					return y_;
				case 2:
					return z_;
				default:
					return w_;
				}
			}


			/* ===== 加算 ===== */

			/// <summary>
			/// 加算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>加算結果</returns>
			[[nodiscard]] Float4 operator + (
				const Float4& right
				) const {

				return {
					x_ + right.x_,
					y_ + right.y_,
					z_ + right.z_,
					w_ + right.w_
				};
			}

			/// <summary>
			/// 加算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>加算後の自身参照</returns>
			Float4& operator += (
				const Float4& right
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
			[[nodiscard]] Float4 operator - (
				const Float4& right
				) const {

				return {
					x_ - right.x_,
					y_ - right.y_,
					z_ - right.z_,
					w_ - right.w_
				};
			}

			/// <summary>
			/// 減算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>減算後の自身参照</returns>
			Float4& operator -= (
				const Float4& right
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
			[[nodiscard]] Float4 operator * (
				const Float4& right
				) const {

				return {
					x_ * right.x_,
					y_ * right.y_,
					z_ * right.z_,
					w_ * right.w_
				};
			}

			/// <summary>
			/// 乗算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>乗算後の自身参照</returns>
			Float4& operator *= (
				const Float4& right
				) {

				*this = *this * right;

				return *this;
			}

			/// <summary>
			/// スカラー倍乗算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>乗算結果</returns>
			[[nodiscard]] Float4 operator * (
				float right
				) const {

				return {
					x_ * right,
					y_ * right,
					z_ * right,
					w_ * right
				};
			}

			/// <summary>
			/// スカラー倍乗算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>乗算後の自身参照</returns>
			Float4& operator *= (
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
			[[nodiscard]] Float4 operator / (
				const Float4& right
				) const {

				return {
					x_ / right.x_,
					y_ / right.y_,
					z_ / right.z_,
					w_ / right.w_
				};
			}

			/// <summary>
			/// 除算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>除算後の自身参照</returns>
			Float4& operator /= (
				const Float4& right
				) {

				*this = *this / right;

				return *this;
			}

			/// <summary>
			/// スカラー倍除算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>除算結果</returns>
			[[nodiscard]] Float4 operator / (
				float right
				) const {

				return {
					x_ / right,
					y_ / right,
					z_ / right,
					w_ / right
				};
			}

			/// <summary>
			/// スカラー倍除算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>除算後の自身参照</returns>
			Float4& operator /= (
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
				const Float4& right
				) const {

				return (
					x_ == right.x_ && 
					y_ == right.y_ && 
					z_ == right.z_ &&
					w_ == right.w_ 
					);
			}

			/// <summary>
			/// 非等値比較演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>比較結果</returns>
			[[nodiscard]] bool operator != (
				const Float4& right
				) const {

				return !(*this == right);
			}


			/* ===== その他 ===== */

			/// <summary>
			/// 符号反転演算子
			/// </summary>
			/// <returns></returns>
			Float4 operator - () const {

				return {
					-x_,
					-y_,
					-z_,
					-w_
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
					y_ * y_ +
					z_ * z_ +
					w_ * w_
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
			Float4& normalize() {

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
			[[nodiscard]] Float4 normalized() const {

				const auto length = this->length();

				if (length != 0.0f) {
					return *this / length;
				}

				return *this;
			}

		};
	}
}