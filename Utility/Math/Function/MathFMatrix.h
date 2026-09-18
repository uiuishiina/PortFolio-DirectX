#pragma once
#include"MathF.h"
#include"../BaseStruct/Float3.h"
#include"../BaseStruct/Quaternion.h"
#include"../BaseStruct/Matrix.h"
#include<optional>

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

			/* ========== 行列数学 ========== */

			/* ===== 作成関数 ===== */

			/// <summary>
			/// 単位行列作成関数
			/// </summary>
			/// <returns>単位行列</returns>
			[[nodiscard]] inline Matrix matrix_identity() {
				return {};
			}

			/// <summary>
			/// 平行移動行列作成関数
			/// </summary>
			/// <param name="translation">平行移動量</param>
			/// <returns>平行移動行列</returns>
			[[nodiscard]] inline Matrix translation_to_matrix(
				const Float3& translation
			) {

				Matrix result{};

				result[0][3] = translation.x_;
				result[1][3] = translation.y_;
				result[2][3] = translation.z_;

				return result;
			}

			/// <summary>
			/// 回転行列作成関数
			/// </summary>
			/// <param name="quaternion">対象クォータニオン</param>
			/// <returns>回転行列</returns>
			[[nodiscard]] inline Matrix quaternion_to_matrix(
				const Quaternion& quaternion
			) {

				const float x = quaternion.x_;
				const float y = quaternion.y_;
				const float z = quaternion.z_;
				const float w = quaternion.w_;

				const float xx = x * x;
				const float yy = y * y;
				const float zz = z * z;

				const float xy = x * y;
				const float xz = x * z;
				const float yz = y * z;

				const float wx = w * x;
				const float wy = w * y;
				const float wz = w * z;

				return Matrix{
					Float4{
						1.0f - 2.0f * (yy + zz),
						2.0f * (xy - wz),
						2.0f * (xz + wy),
						0.0f
					},
					Float4{
						2.0f * (xy + wz),
						1.0f - 2.0f * (xx + zz),
						2.0f * (yz - wx),
						0.0f
					},
					Float4{
						2.0f * (xz - wy),
						2.0f * (yz + wx),
						1.0f - 2.0f * (xx + yy),
						0.0f
					},
					Float4{
						0.0f,
						0.0f,
						0.0f,
						1.0f
					}
				};
			}

			/// <summary>
			/// X軸回転行列作成関数
			/// </summary>
			/// <param name="radian">回転角度（ラジアン）</param>
			/// <returns>X軸回転行列</returns>
			[[nodiscard]] inline Matrix rotate_x(
				float radian
			) {

				const float c = MathF::cos(radian);
				const float s = MathF::sin(radian);

				return Matrix{
					Float4{ 1.0f, 0.0f, 0.0f, 0.0f },
					Float4{ 0.0f,    c,    s, 0.0f },
					Float4{ 0.0f,   -s,    c, 0.0f },
					Float4{ 0.0f, 0.0f, 0.0f, 1.0f }
				};
			}

			/// <summary>
			/// Y軸回転行列作成関数
			/// </summary>
			/// <param name="radian">回転角度（ラジアン）</param>
			/// <returns>Y軸回転行列</returns>
			[[nodiscard]] inline Matrix rotate_y(
				float radian
			) {

				const float c = MathF::cos(radian);
				const float s = MathF::sin(radian);

				return Matrix{
					Float4{    c, 0.0f,   -s, 0.0f },
					Float4{ 0.0f, 1.0f, 0.0f, 0.0f },
					Float4{    s, 0.0f,    c, 0.0f },
					Float4{ 0.0f, 0.0f, 0.0f, 1.0f }
				};
			}

			/// <summary>
			/// Z軸回転行列作成関数
			/// </summary>
			/// <param name="radian">回転角度（ラジアン）</param>
			/// <returns>Z軸回転行列</returns>
			[[nodiscard]] inline Matrix rotate_z(
				float radian
			) {

				const float c = MathF::cos(radian);
				const float s = MathF::sin(radian);

				return Matrix{
					Float4{    c,    s, 0.0f, 0.0f },
					Float4{   -s,    c, 0.0f, 0.0f },
					Float4{ 0.0f, 0.0f, 1.0f, 0.0f },
					Float4{ 0.0f, 0.0f, 0.0f, 1.0f }
				};
			}

			/// <summary>
			/// 拡大率行列作成関数
			/// </summary>
			/// <param name="scale">XYZの拡大率</param>
			/// <returns>拡大率行列</returns>
			[[nodiscard]] inline Matrix scale_to_matrix(
				const Float3& scale
			) {

				return Matrix{ scale };
			}

			/// <summary>
			/// トランスフォーム行列作成関数
			/// </summary>
			/// <details>
			/// 拡大率・回転・平行移動を利用して作成
			/// </details>
			/// <param name="translation">平行移動量</param>
			/// <param name="rotation">回転クォータニオン</param>
			/// <param name="scale">拡大率</param>
			/// <returns>変換行列</returns>
			[[nodiscard]] inline Matrix transform_to_matrix(
				const Float3& translation,
				const Quaternion& rotation,
				const Float3& scale
			) {

				return (
					MathF::translation_to_matrix(translation) *
					MathF::quaternion_to_matrix(rotation) *
					MathF::scale_to_matrix(scale)
					);
			}


			/* ===== 変換関数 ===== */
			
			/// <summary>
			/// 平行移動ベクトル取得関数
			/// </summary>
			/// <param name="translation">取得する行列</param>
			/// <returns>取得した平行移動ベクトル</returns>
			[[nodiscard]] inline Float3 translation_from_matrix(
				const Matrix& matrix
			) {

				return {
					matrix[0][3],
					matrix[1][3],
					matrix[2][3]
				};
			}

			/// <summary>
			/// クォータニオン取得関数
			/// </summary>
			/// <param name="matrix">取得する行列</param>
			/// <returns>作成したクォータニオン</returns>
			[[nodiscard]] inline Quaternion quaternion_from_matrix(
				const Matrix& matrix
			) {

				const auto m00 = matrix[0][0];
				const auto m11 = matrix[1][1];
				const auto m22 = matrix[2][2];
				const auto trace = m00 + m11 + m22;

				Quaternion result{};

				if (trace > 0.0f) {

					const auto s = MathF::sqrt(trace + 1.0f) * 2.0f;

					result.w_ = 0.25f * s;
					result.x_ = (matrix[2][1] - matrix[1][2]) / s;
					result.y_ = (matrix[0][2] - matrix[2][0]) / s;
					result.z_ = (matrix[1][0] - matrix[0][1]) / s;
				}
				else if (
					m00 > m11 &&
					m00 > m22
					) {

					const auto s = MathF::sqrt(
						1.0f + m00 - m11 - m22
					) * 2.0f;

					result.w_ = (matrix[2][1] - matrix[1][2]) / s;
					result.x_ = 0.25f * s;
					result.y_ = (matrix[0][1] + matrix[1][0]) / s;
					result.z_ = (matrix[0][2] + matrix[2][0]) / s;
				}
				else if (m11 > m22) {

					const auto s = MathF::sqrt(
						1.0f + m11 - m00 - m22
					) * 2.0f;

					result.w_ = (matrix[0][2] - matrix[2][0]) / s;
					result.x_ = (matrix[0][1] + matrix[1][0]) / s;
					result.y_ = 0.25f * s;
					result.z_ = (matrix[1][2] + matrix[2][1]) / s;
				}
				else {

					const auto s = MathF::sqrt(
						1.0f + m22 - m00 - m11
					) * 2.0f;

					result.w_ = (matrix[1][0] - matrix[0][1]) / s;
					result.x_ = (matrix[0][2] + matrix[2][0]) / s;
					result.y_ = (matrix[1][2] + matrix[2][1]) / s;
					result.z_ = 0.25f * s;
				}

				return result.normalized();
			}

			/// <summary>
			/// 拡大率取得関数
			/// </summary>
			/// <param name="matrix">取得する行列</param>
			/// <returns>取得した拡大率</returns>
			[[nodiscard]] inline Float3 scale_from_matrix(
				const Matrix& matrix
			) {

				return {
					MathF::sqrt(
						matrix[0][0] * matrix[0][0] +
						matrix[1][0] * matrix[1][0] +
						matrix[2][0] * matrix[2][0]
					),
					MathF::sqrt(
						matrix[0][1] * matrix[0][1] +
						matrix[1][1] * matrix[1][1] +
						matrix[2][1] * matrix[2][1]
					),
					MathF::sqrt(
						matrix[0][2] * matrix[0][2] +
						matrix[1][2] * matrix[1][2] +
						matrix[2][2] * matrix[2][2]
					)
				};
			}


			/* ========== 適用関数 ========== */

			/// <summary>
			/// 平行移動ベクトル適応関数
			/// </summary>
			/// <param name="matrix">適応先行列</param>
			/// <param name="translation">適用するベクトル</param>
			/// <returns>適応した行列</returns>
			[[nodiscard]] inline Matrix apply_translation(
				const Matrix& matrix,
				const Float3& translation
			) {

				return matrix * MathF::translation_to_matrix(translation);
			}

			/// <summary>
			/// クオータニオン適応関数
			/// </summary>
			/// <param name="matrix">適応先行列</param>
			/// <param name="rotation">適用するクオータニオン</param>
			/// <returns>適応した行列</returns>
			[[nodiscard]] inline Matrix apply_rotation(
				const Matrix& matrix,
				const Quaternion& rotation
			) {

				return matrix * MathF::quaternion_to_matrix(rotation);
			}

			/// <summary>
			/// 拡大率適応関数
			/// </summary>
			/// <param name="matrix">適応先行列</param>
			/// <param name="scale">適用する拡大率</param>
			/// <returns>適応した行列</returns>
			[[nodiscard]] inline Matrix apply_scale(
				const Matrix& matrix,
				const Float3& scale
			) {

				return matrix * MathF::scale_to_matrix(scale);
			}

			/// <summary>
			/// トランスフォーム適応関数
			/// </summary>
			/// <param name="matrix">適応先行列</param>
			/// <param name="translation">適用するベクトル</param>
			/// <param name="rotation">適用するクオータニオン</param>
			/// <param name="scale">適用する拡大率</param>
			/// <returns>適応した行列</returns>
			[[nodiscard]] inline Matrix apply_transform(
				const Matrix& matrix,
				const Float3& translation,
				const Quaternion& rotation,
				const Float3& scale
			) {

				return matrix * MathF::transform_to_matrix(
					translation,
					rotation,
					scale
				);
			}

		}
	}
}