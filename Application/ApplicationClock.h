#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"

#include<thread>
#include<chrono>
#include<cassert>

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	/// <summary>
	/// アプリケーション時計クラス
	/// </summary>
	class ApplicationClock final : HandyItems::others::NonCopyableBase
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="period_value">フレーム間隔設定 (ミリ秒)</param>
		explicit ApplicationClock(
			std::uint32_t period_value
		) :
			period_{ std::chrono::milliseconds{ period_value } } {

			assert(period_value && "ApplicationClock period must not be zero");
			initialize_clock();
		}

		/* ===== 初期化関数 ===== */

		/// <summary>
		/// 時計初期化関数
		/// </summary>
		void initialize_clock() {

			next_time = get_now();
			last_time = get_now();

			next_time += period_;
		}

		/// <summary>
		/// フレーム待機関数
		/// </summary>
		void wait() {

			//	設定した時間まで待機
			std::this_thread::sleep_until(next_time);
			next_time += period_;
		}

		/// <summary>
		/// 遅延調整関数
		/// </summary>
		/// <param name="tolerance">許容する遅延 (ミリ秒)</param>
		/// <returns>調整の際に経過したフレーム数... [ 1なら通常待機 ]</returns>
		std::uint32_t wait_fixed_to_skip(
			std::uint32_t tolerance
		) {

			const auto toler = static_cast<std::chrono::milliseconds>(tolerance);
			const auto now = get_now();

			std::uint32_t skip = 1;

			//	調整
			if (next_time + toler < now)
			{
				const auto late = now - next_time;

				skip = static_cast<std::uint32_t>(late / period_ + 1);

				next_time += period_ * skip;
			}

			wait();

			return skip;
		}

		bool alredy_second() {

			const auto now = get_now();
			second_ += std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time);
			last_time = now;

			if (second_ >= std::chrono::seconds{ 1 }) {
				second_ -= std::chrono::seconds{ 1 };
				return true;
			}
			return false;
		}

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// フレーム間隔設定 (ミリ秒)
		/// </summary>
		std::chrono::milliseconds period_{};

		/// <summary>
		/// 次回待機時間設定
		/// </summary>
		std::chrono::time_point<std::chrono::steady_clock> next_time{};

		std::chrono::milliseconds second_{};
		std::chrono::time_point<std::chrono::steady_clock> last_time{};

		const std::chrono::steady_clock::time_point get_now() {
			return std::chrono::steady_clock::now();
		}

	};
}