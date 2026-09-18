#pragma once
#include "../BaseStruct/Quaternion.h"
#include "../BaseStruct/Float3.h"
#include "../Function/MathFFloat3.h"
#include "../BaseStruct/Float4.h"

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

			/* ========== クォータニオン用関数 ========== */

			/* -- 作成関数 -- */

			/// <summary>
			/// 単位クォータニオン作成関数
			/// </summary>
			/// <returns>作成した単位クォータニオン</returns>
			[[nodiscard]] Quaternion quaternion_identity() {

				return {
					0.0f,
					0.0f,
					0.0f,
					1.0f
				};
			}

			/// <summary>
			/// クォータニオン作成関数
			/// </summary>
			/// <details>
			/// ベクトルからクォータニオンを作成
			/// </details>
			/// <param name="axis">回転軸</param>
			/// <param name="angle">回転角度（ラジアン）</param>
			/// <returns>作成したクォータニオン</returns>
			[[nodiscard]] Quaternion from_axis_angle(
				Float3 axis,
				float angle
			) {

				//	ゼロベクトルなら単位クオータニオンを返す
				if (axis.length_squared() == 0.0f) {
					return quaternion_identity();
				}

				//	正規化してから計算
				axis.normalize();

				const float half_angle = angle * HALF;
				const float sin_half = MathF::sin(half_angle);
				const float cos_half = MathF::cos(half_angle);

				return {
					axis.x_ * sin_half,
					axis.y_ * sin_half,
					axis.z_ * sin_half,
					cos_half
				};
			}

			/// <summary>
			/// クォータニオン作成関数
			/// </summary>
			/// <details>
			/// オイラー角からクォータニオンを作成する関数
			/// </details>
			/// <param name="euler">オイラー角（X、Y、Z / ラジアン）</param>
			/// <returns>作成したクォータニオン</returns>
			[[nodiscard]] Quaternion from_euler(
				const Float3& euler
			) {

				const float half_x = euler.x_ * MathF::HALF;
				const float half_y = euler.y_ * MathF::HALF;
				const float half_z = euler.z_ * MathF::HALF;

				const float sx = MathF::sin(half_x);
				const float cx = MathF::cos(half_x);

				const float sy = MathF::sin(half_y);
				const float cy = MathF::cos(half_y);

				const float sz = MathF::sin(half_z);
				const float cz = MathF::cos(half_z);

				const Quaternion qx{
					sx,
					0.0f,
					0.0f,
					cx
				};

				const Quaternion qy{
					0.0f,
					sy,
					0.0f,
					cy
				};

				const Quaternion qz{
					0.0f,
					0.0f,
					sz,
					cz
				};

				return qx * qy * qz;
			}


			/* -- 利用関数 -- */

			/// <summary>
			/// ベクトル回転関数
			/// </summary>
			/// <details>
			/// クォータニオンを利用したベクトル回転
			/// </details>
			/// <param name="quaternion">回転を表すクォータニオン</param>
			/// <param name="vector">回転対象のベクトル</param>
			/// <returns>回転後のベクトル</returns>
			[[nodiscard]] inline Float3 rotate(
				const Quaternion& quaternion,
				const Float3& vector
			) {

				//	正規化して利用
				const Quaternion q = quaternion.normalized();

				//	ベクトルからクオータニオン作成
				const Quaternion point{
					vector.x_,
					vector.y_,
					vector.z_,
					0.0f
				};

				const auto result = q * point * q.conjugate();

				return {
					result.x_,
					result.y_,
					result.z_
				};
			}

			/// <summary>
			/// オイラー角取得関数
			/// </summary>
			/// <details>
			/// クォータニオンからオイラー角を取得する関数
			/// </details>
			/// <param name="quaternion">対象クォータニオン</param>
			/// <returns>XYZ順のオイラー角（ラジアン）</returns>
			[[nodiscard]] inline Float3 euler(
				const Quaternion& quaternion
			) {
				//	正規化したものを利用
				const Quaternion q = quaternion.normalized();

				const auto x = q.x_;
				const auto y = q.y_;
				const auto z = q.z_;
				const auto w = q.w_;

				float angle_x{}, angle_y{}, angle_z{};

				const auto sin_y = 2.0f * (x * z + w * y);
				constexpr float epsilon = 1.0e-6f;

				// ジンバルロック判定(Xにまとめる)
				if (sin_y >= 1.0f - epsilon) {

					return {
						MathF::wrap_angle(2.0f * MathF::atan2(z, y)),
						MathF::HALF_PI,
						ZEROF
					};
				}

				if (sin_y <= -1.0f + epsilon) {

					return {
						MathF::wrap_angle(2.0f * MathF::atan2(z, y)),
						-MathF::HALF_PI,
						ZEROF
					};
				}

				{
					// X軸回転

					/*
					sin(X) = 2 * (w * x - y * z)
					cos(X) = 1 - 2 * (x * x + y * y)
					*/
					const auto sin_x = 2.0f * (w * x - y * z);

					const auto cos_x = 1.0f - 2.0f * (x * x + y * y);

					angle_x = MathF::atan2(
						sin_x,
						cos_x
					);
				}

				
				{
					// Y軸回転

					/*
					q = qx * qy * qz
					sin(Y) = 2 * (x * z + w * y)
					*/

					angle_y = MathF::asin(
						MathF::clamp(
							sin_y,
							-1.0f,
							1.0f
						)
					);
				}

				{

					// Z軸回転

					/*
					sin(Z) = 2 * (w * z - x * y)
					cos(Z) = 1 - 2 * (y * y + z * z)
					*/

					const auto sin_z = 2.0f * (w * z - x * y);

					const auto cos_z = 1.0f - 2.0f * (y * y + z * z);

					angle_z = MathF::atan2(
						sin_z,
						cos_z
					);
				}

				return {
					angle_x,
					angle_y,
					angle_z
				};
			}

			/// <summary>
			/// 内積取得関数
			/// </summary>
			/// <details>
			/// クォータニオンの内積を取得する関数
			/// </details>
			/// <param name="left">左辺クォータニオン</param>
			/// <param name="right">右辺クォータニオン</param>
			/// <returns>内積</returns>
			[[nodiscard]] inline float dot(
				const Quaternion& left,
				const Quaternion& right
			) {

				return (
					left.x_ * right.x_ +
					left.y_ * right.y_ +
					left.z_ * right.z_ +
					left.w_ * right.w_
					);
			}

			/// <summary>
			/// 角度差取得関数
			/// </summary>
			/// <details>
			/// 2つのクォータニオン間の角度を取得する関数
			/// </summary>
			/// <param name="left">左辺クォータニオン</param>
			/// <param name="right">右辺クォータニオン</param>
			/// <returns>角度（ラジアン）</returns>
			[[nodiscard]] inline float angle(
				const Quaternion& left,
				const Quaternion& right
			) {

				const Quaternion q1 = left.normalized();
				const Quaternion q2 = right.normalized();

				const float d = MathF::abs(
					dot(q1, q2)
				);

				return 2.0f * MathF::acos(
					MathF::clamp(d)	// [ 0 ～ 1 ] 制限
				);
			}

			/// <summary>
			/// 回転クォータニオン作成関数
			/// </summary>
			/// <details>
			/// 方向Aから方向Bへの回転クォータニオンを作成する関数
			/// </details>
			/// <param name="from">回転前の方向</param>
			/// <param name="to">回転後の方向</param>
			/// <returns>回転クォータニオン</returns>
			[[nodiscard]] Quaternion from_to(
				Float3 from,
				Float3 to
			) {

				constexpr float epsilon = 1.0e-6f;

				if (
					from.length_squared() <= epsilon ||
					to.length_squared() <= epsilon
					) {
					return quaternion_identity();
				}

				from.normalize();
				to.normalize();

				const float d = MathF::dot(from, to);

				// 同じ方向
				if (d >= 1.0f - epsilon) {
					return quaternion_identity();
				}

				// 反対方向
				if (d <= -1.0f + epsilon) {

					// from と直交する適当な軸を選択
					Float3 axis;

					if (MathF::abs(from.x_) < MathF::abs(from.y_)) {
						axis = {
							0.0f,
							-from.z_,
							from.y_
						};
					}
					else {
						axis = {
							-from.z_,
							0.0f,
							from.x_
						};
					}

					axis.normalize();

					return from_axis_angle(
						axis,
						MathF::PI
					);
				}

				// 外積
				const Float3 axis = MathF::cross(from, to);

				const float s = MathF::sqrt(
					2.0f * (1.0f + d)
				);

				const float inv_s = 1.0f / s;

				return {
					axis.x_ * inv_s,
					axis.y_ * inv_s,
					axis.z_ * inv_s,
					s * 0.5f
				};
			}

			/// <summary>
			/// クォータニオン線形補間関数
			/// </summary>
			/// <details>
			/// クォータニオンの線形補間を行う関数(正規化なし)
			/// </details>
			/// <param name="start">開始クォータニオン</param>
			/// <param name="end">終了クォータニオン</param>
			/// <param name="t">補間係数</param>
			/// <returns>補間結果(正規化なし)</returns>
			[[nodiscard]] inline Quaternion lerp(
				const Quaternion& start,
				const Quaternion& end,
				float t
			) {

				return start * (1.0f - t) + end * t;
			}

			/// <summary>
			/// クォータニオン正規化線形補間関数
			/// </summary>
			/// <details>
			/// クォータニオンの正規化線形補間を行う関数
			/// </details>
			/// <param name="start">開始クォータニオン</param>
			/// <param name="end">終了クォータニオン</param>
			/// <param name="t">補間係数</param>
			/// <returns>補間結果</returns>
			[[nodiscard]] inline Quaternion nlerp(
				const Quaternion& start,
				const Quaternion& end,
				float t
			) {

				Quaternion a = start.normalized();
				Quaternion b = end.normalized();

				if (dot(a, b) < 0.0f) {
					b = -b;
				}

				return (
					a * (1.0f - t) +
					b * t
					).normalized();
			}

			/// <summary>
			/// クォータニオン球面線形補間関数
			/// </summary>
			/// <details>
			/// クォータニオンの球面線形補間を行う関数(正規化あり)
			/// </summary>
			/// <param name="start">開始クォータニオン</param>
			/// <param name="end">終了クォータニオン</param>
			/// <param name="t">補間係数</param>
			/// <returns>補間結果(正規化あり)</returns>
			[[nodiscard]] inline Quaternion slerp(
				const Quaternion& start,
				const Quaternion& end,
				float t
			) {

				Quaternion a = start.normalized();
				Quaternion b = end.normalized();

				float d = dot(a, b);

				// 最短経路を選択
				if (d < 0.0f) {
					b = -b;
					d = -d;
				}

				d = MathF::clamp(d, -1.0f, 1.0f);

				constexpr float epsilon = 1.0e-6f;

				// ほぼ同じ回転なら nlerp
				if (d > 1.0f - epsilon) {

					Quaternion result =
						a * (1.0f - t) +
						b * t;

					return result.normalized();
				}

				const auto theta = MathF::acos(d);
				const auto sin_theta = MathF::sin(theta);

				const auto weight_a = MathF::sin((1.0f - t) * theta) / sin_theta;
				const auto weight_b = MathF::sin(t * theta) / sin_theta;

				return (
					a * weight_a +
					b * weight_b
					).normalized();
			}

		}
	}
}