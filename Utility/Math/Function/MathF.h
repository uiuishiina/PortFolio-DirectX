#pragma once
#include<cmath>

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

			/* ========== 定数定義 ========== */

			/// <summary>
			/// ０定数
			/// </summary>
			inline constexpr float ZEROF = 0.0f;

			/// <summary>
			/// 1/2定数
			/// </summary>
			inline constexpr float HALF = 0.5f;

			/* -- 円周率定義 -- */

			/// <summary>
			/// 円周率
			/// </summary>
			inline constexpr float PI = 3.14159265358979323846f;

			/// <summary>
			/// 二倍円周率
			/// </summary>
			inline constexpr float Double_PI = PI * 2.0f;

			/// <summary>
			/// 1/2円周率
			/// </summary>
			inline constexpr float HALF_PI = PI * HALF;


			/* ========== 基礎数学 ========== */

			/* ===== 三角関数 ===== */

			/// <summary>
			/// SIN計算関数
			/// </summary>
			/// <param name="value">角度（ラジアン）</param>
			/// <returns>[ SIN ] の計算結果</returns>
			[[nodiscard]] inline float sin(
				float value
			) {

				return std::sin(value);
			}

			/// <summary>
			/// COS計算関数
			/// </summary>
			/// <param name="value">角度（ラジアン）</param>
			/// <returns>[ COS ] の計算結果</returns>
			[[nodiscard]] inline float cos(
				float value
			) {

				return std::cos(value);
			}

			/// <summary>
			/// TAN計算関数
			/// </summary>
			/// <param name="value">角度（ラジアン）</param>
			/// <returns>[ TAN ] の計算結果</returns>
			[[nodiscard]] inline float tan(
				float value
			) {

				return std::tan(value);
			}


			/* ===== 逆三角関数 ===== */

			/// <summary>
			/// ASIN計算関数
			/// </summary>
			/// <param name="value">計算する値</param>
			/// <returns>[ ASIN ] の計算結果 [ 角度（ラジアン）]</returns>
			[[nodiscard]] inline float asin(
				float value
			) {

				return std::asin(value);
			}

			/// <summary>
			/// ACOS計算関数
			/// </summary>
			/// <param name="value">計算する値</param>
			/// <returns>[ ACOS ] の計算結果 [ 角度（ラジアン）]</returns>
			[[nodiscard]] inline float acos(
				float value
			) {

				return std::acos(value);
			}

			/// <summary>
			/// ATAN計算関数
			/// </summary>
			/// <param name="value">計算する値</param>
			/// <returns>[ ATAN ] の計算結果 [ 角度（ラジアン）]</returns>
			[[nodiscard]] inline float atan(
				float value
			) {

				return std::atan(value);
			}

			/// <summary>
			/// ATAN2計算関数
			/// </summary>
			/// <param name="y">[ Y軸 ] の値</param>
			/// <param name="x">[ X軸 ] の値</param>
			/// <returns>[ ATAN2 ] の計算結果 [ 角度（ラジアン）]</returns>
			[[nodiscard]] inline float atan2(
				float y, 
				float x
			) {

				return std::atan2(y, x);
			}


			/* ===== 数値制限 ===== */

			/// <summary>
			/// 最小値取得関数
			/// </summary>
			/// <param name="left">比較する左辺値</param>
			/// <param name="right">比較する右辺値</param>
			/// <returns>[ 小さい方 ] の値</returns>
			[[nodiscard]] inline float min(
				float left,
				float right
			) {

				return left < right ? left : right;
			}

			/// <summary>
			/// 最大値取得関数
			/// </summary>
			/// <param name="left">比較する左辺値</param>
			/// <param name="right">比較する右辺値</param>
			/// <returns>[ 大きい方 ] の値</returns>
			[[nodiscard]] inline float max(
				float left, 
				float right
			) {

				return left > right ? left : right;
			}

			/// <summary>
			/// Clamp関数
			/// </summary>
			/// <param name="value">制限する値</param>
			/// <param name="min">最小値... デフォルト[ 0 ]</param>
			/// <param name="max">最大値... デフォルト[ 1 ]</param>
			/// <returns>[ 範囲内に制限 ] された値</returns>
			[[nodiscard]] inline float clamp(
				float value,
				float min = 0.0f,
				float max = 1.0f
			) {

				if (min <= value && value <= max) {
					return value;
				}
				else if (value < min) {
					return min;
				}
				else {
					return max;
				}
			}


			/* ===== 数値計算 ===== */

			/// <summary>
			/// 平方根計算関数
			/// </summary>
			/// <param name="value">計算する値</param>
			/// <returns>[ 平方根 ] の計算結果</returns>
			[[nodiscard]] inline float sqrt(
				float value
			) {

				return std::sqrt(value);
			}

			/// <summary>
			/// 絶対値計算関数
			/// </summary>
			/// <param name="value">計算する値</param>
			/// <returns>[ 絶対値 ] の計算結果</returns>
			[[nodiscard]] inline float abs(
				float value
			) {

				return std::abs(value);
			}

			/// <summary>
			/// 角度正規化関数
			/// </summary>
			/// <details>
			/// 角度を -PI ～ PI の範囲へ正規化する関数
			/// </details>
			/// <param name="angle">角度（ラジアン）</param>
			/// <returns>正規化された角度（ラジアン）</returns>
			[[nodiscard]] inline float wrap_angle(
				float angle
			) {

				angle = std::fmod(
					angle + PI,
					Double_PI
				);

				if (angle < 0.0f) {
					angle += Double_PI;
				}

				return angle - PI;
			}

			/// <summary>
			/// 度数変換関数
			/// </summary>
			/// <details>
			/// 度数からラジアンへ変換する関数
			/// </details>
			/// <param name="degrees">角度（度）</param>
			/// <returns>角度（ラジアン）</returns>
			[[nodiscard]] inline float deg_to_rad(
				float degrees
			) {

				return degrees * (PI / 180.0f);
			}

			/// <summary>
			/// ラジアン変換関数
			/// </summary>
			/// <details>
			/// ラジアンから度へ変換する関数
			/// </details>
			/// <param name="radians">角度（ラジアン）</param>
			/// <returns>角度（度）</returns>
			[[nodiscard]] inline float rad_to_deg(
				float radians
			) {

				return radians * (180.0f / PI);
			}

			/// <summary>
			/// 浮動小数点等値判定関数
			/// </summary>
			/// <details>
			/// 浮動小数点値がほぼ等しいか判定する関数
			/// </details>
			/// <param name="left">左辺値</param>
			/// <param name="right">右辺値</param>
			/// <param name="epsilon">許容誤差</param>
			/// <returns>ほぼ等しい場合は [ true ]</returns>
			[[nodiscard]] inline bool approximately(
				float left,
				float right,
				float epsilon = 1.0e-6f
			) {

				return abs(left - right) <= epsilon;
			}

			/// <summary>
			/// 符号取得関数
			/// </summary>
			/// <param name="value">対象値</param>
			/// <returns>正なら [ 1 ]、負なら [ -1 ]、0なら [ 0 ]</returns>
			[[nodiscard]] inline float sign(
				float value
			) {

				if (value > ZEROF) {
					return 1.0f;
				}
				else if (value < ZEROF) {
					return -1.0f;
				}
				else {
					return ZEROF;
				}
			}

			/// <summary>
			/// 線形補間行関数
			/// </summary>
			/// <details>
			/// 線形補間を行う関数
			/// </details>
			/// <param name="start">開始値</param>
			/// <param name="end">終了値</param>
			/// <param name="t">補間係数</param>
			/// <returns>補間結果</returns>
			[[nodiscard]] inline float lerp(
				float start,
				float end,
				float t
			) {

				return start + (end - start) * t;
			}

			[[nodiscard]] inline float floor(
				float value
			) {

				return std::floor(value);
			}

			[[nodiscard]] inline float ceil(
				float value
			) {

				return std::ceil(value);
			}

		}
	}
}