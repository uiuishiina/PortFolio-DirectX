#pragma once
#include"Float3.h"
#include"Float4.h"
#include<optional>
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
		/// 行列構造体
		/// </summary>
		/// <details>
		/// 4行4列の行列。
		/// 列ベクトルを使用し、行単位で保持する。
		/// </details>
		struct Matrix {

			/* ========== メンバー変数 ========== */

			/// <summary>
			/// 行列の各行
			/// </summary>
			Float4 matrix_[4] = {
				{ 1.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			};

			/* ========== メンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			Matrix() = default;

			/// <summary>
			/// 行指定コンストラクタ
			/// </summary>
			/// <param name="row0">0行目</param>
			/// <param name="row1">1行目</param>
			/// <param name="row2">2行目</param>
			/// <param name="row3">3行目</param>
			Matrix(
				const Float4& row0,
				const Float4& row1,
				const Float4& row2,
				const Float4& row3
			) :
				matrix_{ row0, row1, row2, row3 } {}

			/// <summary>
			/// XYZの対角成分指定コンストラクタ
			/// </summary>
			/// <param name="diagonal">XYZの対角成分</param>
			Matrix(
				const Float3& diagonal
			) :
				matrix_{
					{ diagonal.x_, 0.0f, 0.0f, 0.0f },
					{ 0.0f, diagonal.y_, 0.0f, 0.0f },
					{ 0.0f, 0.0f, diagonal.z_, 0.0f },
					{ 0.0f, 0.0f, 0.0f, 1.0f }
			} {}

			/// <summary>
			/// 対角成分指定コンストラクタ
			/// </summary>
			/// <param name="diagonal">対角成分</param>
			Matrix(
				const Float4& diagonal
			) :
				matrix_{
					{ diagonal.x_, 0.0f, 0.0f, 0.0f },
					{ 0.0f, diagonal.y_, 0.0f, 0.0f },
					{ 0.0f, 0.0f, diagonal.z_, 0.0f },
					{ 0.0f, 0.0f, 0.0f, diagonal.w_ }
			} {}


			/* ========== 演算子オーバーロード ========== */

			/* ===== アクセス ===== */

			/// <summary>
			/// 行アクセス演算子
			/// </summary>
			/// <param name="index">行番号</param>
			/// <returns>指定した行への参照</returns>
			[[nodiscard]] Float4& operator[] (
				std::size_t index
				) {

				assert(index < 4 && "Matrix index out of range");

				return matrix_[index];
			}

			/// <summary>
			/// 行アクセス演算子
			/// </summary>
			/// <param name="index">行番号</param>
			/// <returns>指定した行へのConst参照</returns>
			[[nodiscard]] const Float4& operator[] (
				std::size_t index
				) const {

				assert(index < 4 && "Matrix index out of range");

				return matrix_[index];
			}


			/* ===== 加算 ===== */

			/// <summary>
			/// 加算演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>加算結果</returns>
			[[nodiscard]] Matrix operator + (
				const Matrix& right
				) const {

				return {
					matrix_[0] + right.matrix_[0],
					matrix_[1] + right.matrix_[1],
					matrix_[2] + right.matrix_[2],
					matrix_[3] + right.matrix_[3]
				};
			}

			/// <summary>
			/// 加算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>加算後の自身参照</returns>
			Matrix& operator += (
				const Matrix& right
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
			[[nodiscard]] Matrix operator - (
				const Matrix& right
				) const {

				return {
					matrix_[0] - right.matrix_[0],
					matrix_[1] - right.matrix_[1],
					matrix_[2] - right.matrix_[2],
					matrix_[3] - right.matrix_[3]
				};
			}

			/// <summary>
			/// 減算代入演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>減算後の自身参照</returns>
			Matrix& operator -= (
				const Matrix& right
				) {

				*this = *this - right;

				return *this;
			}


			/* ===== 乗算 ===== */

			/// <summary>
			/// 行列乗算演算子
			/// </summary>
			/// <param name="right">右辺行列</param>
			/// <returns>乗算結果</returns>
			[[nodiscard]] Matrix operator * (
				const Matrix& right
				) const {

				Matrix result{};

				for (std::size_t row = 0; row < 4; ++row) {
					for (std::size_t col = 0; col < 4; ++col) {

						result[row][col] =
							matrix_[row][0] * right[0][col] +
							matrix_[row][1] * right[1][col] +
							matrix_[row][2] * right[2][col] +
							matrix_[row][3] * right[3][col];
					}
				}

				return result;
			}

			/// <summary>
			/// 行列乗算代入演算子
			/// </summary>
			/// <param name="right">右辺行列</param>
			/// <returns>乗算後の自身参照</returns>
			Matrix& operator *= (
				const Matrix& right
				) {

				*this = *this * right;

				return *this;
			}

			/// <summary>
			/// スカラー倍乗算演算子
			/// </summary>
			/// <param name="right">右辺スカラー値</param>
			/// <returns>乗算結果</returns>
			[[nodiscard]] Matrix operator * (
				float right
				) const {

				return {
					matrix_[0] * right,
					matrix_[1] * right,
					matrix_[2] * right,
					matrix_[3] * right
				};
			}

			/// <summary>
			/// スカラー倍乗算代入演算子
			/// </summary>
			/// <param name="right">右辺スカラー値</param>
			/// <returns>乗算後の自身参照</returns>
			Matrix& operator *= (
				float right
				) {

				*this = *this * right;

				return *this;
			}


			/* ===== 除算 ===== */

			/// <summary>
			/// スカラー倍除算演算子
			/// </summary>
			/// <param name="right">右辺スカラー値</param>
			/// <returns>除算結果</returns>
			[[nodiscard]] Matrix operator / (
				float right
				) const {

				return {
					matrix_[0] / right,
					matrix_[1] / right,
					matrix_[2] / right,
					matrix_[3] / right
				};
			}

			/// <summary>
			/// スカラー倍除算代入演算子
			/// </summary>
			/// <param name="right">右辺スカラー値</param>
			/// <returns>除算後の自身参照</returns>
			Matrix& operator /= (
				float right
				) {

				*this = *this / right;

				return *this;
			}


			/* ===== ベクトル乗算 ===== */

			/// <summary>
			/// 四次元ベクトルとの乗算演算子
			/// </summary>
			/// <param name="right">右辺四次元ベクトル</param>
			/// <returns>変換後の四次元ベクトル</returns>
			[[nodiscard]] Float4 operator * (
				const Float4& right
				) const {

				return {
					matrix_[0][0] * right.x_ +
					matrix_[0][1] * right.y_ +
					matrix_[0][2] * right.z_ +
					matrix_[0][3] * right.w_,

					matrix_[1][0] * right.x_ +
					matrix_[1][1] * right.y_ +
					matrix_[1][2] * right.z_ +
					matrix_[1][3] * right.w_,

					matrix_[2][0] * right.x_ +
					matrix_[2][1] * right.y_ +
					matrix_[2][2] * right.z_ +
					matrix_[2][3] * right.w_,

					matrix_[3][0] * right.x_ +
					matrix_[3][1] * right.y_ +
					matrix_[3][2] * right.z_ +
					matrix_[3][3] * right.w_
				};
			}


			/* ===== 比較 ===== */

			/// <summary>
			/// 等値比較演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>比較結果</returns>
			[[nodiscard]] bool operator == (
				const Matrix& right
				) const {

				return (
					matrix_[0] == right.matrix_[0] &&
					matrix_[1] == right.matrix_[1] &&
					matrix_[2] == right.matrix_[2] &&
					matrix_[3] == right.matrix_[3]
					);
			}

			/// <summary>
			/// 非等値比較演算子
			/// </summary>
			/// <param name="right">右辺値</param>
			/// <returns>比較結果</returns>
			[[nodiscard]] bool operator != (
				const Matrix& right
				) const {

				return !(*this == right);
			}


			/* ===== その他 ===== */

			/// <summary>
			/// 符号反転演算子
			/// </summary>
			/// <returns>符号反転した行列</returns>
			[[nodiscard]] Matrix operator - () const {

				return {
					-matrix_[0],
					-matrix_[1],
					-matrix_[2],
					-matrix_[3]
				};
			}


			/* ========== 数学系関数 ========== */

			/// <summary>
			/// 転置行列取得関数
			/// </summary>
			/// <returns>転置された行列</returns>
			[[nodiscard]] Matrix transpose() const {

				Matrix result{};

				for (std::size_t row = 0; row < 4; ++row) {
					for (std::size_t col = 0; col < 4; ++col) {
						result[row][col] = matrix_[col][row];
					}
				}

				return result;
			}


			/// <summary>
			/// 行列式計算関数
			/// </summary>
			/// <returns>行列式</returns>
			[[nodiscard]] float determinant() const {

				/*
					a,b,c,d
					e,f,g,h
					i,j,k,l
					m,n,o,p
				*/

				const float a = matrix_[0][0];
				const float b = matrix_[0][1];
				const float c = matrix_[0][2];
				const float d = matrix_[0][3];

				const float e = matrix_[1][0];
				const float f = matrix_[1][1];
				const float g = matrix_[1][2];
				const float h = matrix_[1][3];

				const float i = matrix_[2][0];
				const float j = matrix_[2][1];
				const float k = matrix_[2][2];
				const float l = matrix_[2][3];

				const float m = matrix_[3][0];
				const float n = matrix_[3][1];
				const float o = matrix_[3][2];
				const float p = matrix_[3][3];

				return
					a * (
						f * (k * p - l * o) -
						g * (j * p - l * n) +
						h * (j * o - k * n)
						)
					- b * (
						e * (k * p - l * o) -
						g * (i * p - l * m) +
						h * (i * o - k * m)
						)
					+ c * (
						e * (j * p - l * n) -
						f * (i * p - l * m) +
						h * (i * n - j * m)
						)
					- d * (
						e * (j * o - k * n) -
						f * (i * o - k * m) +
						g * (i * n - j * m)
						);
			}

			/// <summary>
			/// 逆行列取得関数
			/// </summary>
			/// <returns>逆行列...ないなら [ std::nullopt ]</returns>
			[[nodiscard]] std::optional<Matrix> inverse() const {

				const auto det = determinant();

				//	逆行列を持たないなら [ std::nullopt ]
				if (MathF::approximately(det, MathF::ZEROF)) {
					return std::nullopt;
				}

				Matrix result{};

				//	余因子行列を作成
				for (std::size_t row = 0; row < 4; ++row) {
					for (std::size_t col = 0; col < 4; ++col) {

						float minor[3][3]{};

						std::size_t minor_row = 0;

						for (std::size_t src_row = 0; src_row < 4; ++src_row) {

							if (src_row == row) {
								continue;
							}

							std::size_t minor_col = 0;

							for (std::size_t src_col = 0; src_col < 4; ++src_col) {

								if (src_col == col) {
									continue;
								}

								minor[minor_row][minor_col] =
									matrix_[src_row][src_col];

								++minor_col;
							}

							++minor_row;
						}

						const auto minor_det =
							minor[0][0] * (
								minor[1][1] * minor[2][2] -
								minor[1][2] * minor[2][1]
								)
							- minor[0][1] * (
								minor[1][0] * minor[2][2] -
								minor[1][2] * minor[2][0]
								)
							+ minor[0][2] * (
								minor[1][0] * minor[2][1] -
								minor[1][1] * minor[2][0]
								);

						const auto cofactor = (
							(row + col) % 2 == 0
							) ?
							minor_det : -minor_det;

						//	余因子行列の転置 = 逆行列
						result[col][row] = cofactor / det;
					}
				}

				return result;
			}

			/// <summary>
			/// 単位行列判定関数
			/// </summary>
			/// <returns>単位行列ならtrue</returns>
			[[nodiscard]] bool is_identity() const {

				const Matrix identity{};

				for (std::size_t row = 0; row < 4; ++row) {
					for (std::size_t col = 0; col < 4; ++col) {

						if (!MathF::approximately(matrix_[row][col], identity[row][col])) {
							return false;
						}
					}
				}

				return true;
			}

			/// <summary>
			/// ゼロ行列判定関数
			/// </summary>
			/// <returns>ゼロ行列ならtrue</returns>
			[[nodiscard]] bool is_zero() const {

				for (std::size_t row = 0; row < 4; ++row) {
					for (std::size_t col = 0; col < 4; ++col) {

						if (!MathF::approximately(matrix_[row][col],MathF::ZEROF)) {
							return false;
						}
					}
				}

				return true;
			}

		};
	}
}