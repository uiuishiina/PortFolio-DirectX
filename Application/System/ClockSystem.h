#pragma once

#include"System.h"

#include<thread>
#include<chrono>
#include<cassert>

namespace App
{

	class ClockSystem final : public ISystem
	{
		using TimePoint = std::chrono::steady_clock::time_point;
	public:
		using Milliseconds = std::chrono::milliseconds;

		explicit ClockSystem(
			uint32_t period_value
		):
			period_{ Milliseconds{ period_value } }
		{
			assert(period_value && "ApplicationClock period must not be zero");
		}


		bool init_system(SystemManager& manager) override
		{
			return true;
		}

		void update_system() override
		{
			const auto now = get_now();

			delta_time = std::chrono::duration_cast<Milliseconds>(now - last_time);

			last_time = now;
		}

		void shutdown_system() override
		{

		}

		void start_clock() {

			start_time = get_now();
			next_time = get_now() + period_;
			last_time = get_now();

			is_active = true;
		}

		void stop_cloack()
		{
			is_active = false;
		}

		bool get_active() const noexcept {
			return is_active;
		}

		Milliseconds get_delta_time() const noexcept
		{
			return delta_time;
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

			const auto toler = static_cast<Milliseconds>(tolerance);
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


	private:

		bool is_active = false;

		/// <summary>
		/// フレーム間隔設定 (ミリ秒)
		/// </summary>
		Milliseconds period_{};

		/// <summary>
		/// 次回待機時間設定
		/// </summary>
		TimePoint next_time{};

		TimePoint start_time{};

		Milliseconds delta_time{};
		TimePoint last_time{};

		const std::chrono::steady_clock::time_point get_now() {
			return std::chrono::steady_clock::now();
		}

	};
}