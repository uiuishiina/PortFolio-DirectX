#pragma once

#include"System.h"
#include"InputSystem.h"
#include"ClockSystem.h"
#include"WindowsSystem.h"
#include"DebugSystem.h"

namespace App
{
	class LoopManager final
	{
	public:

		explicit LoopManager(
			SystemManager* system
		) :
			system_{ system } 
		{
		}

		void run()
		{
			if (!system_)
			{
				return;
			}

			system_->send_update_order();

			if (system_->get_system<WindowsSystem>())
			{
				run_window();
			}
			else
			{
				run_normal();
			}
		}

	private:

		void run_normal()
		{
			auto* input = system_->get_system<InputSystem>();
			if (!input)
			{
				//	終了できないため返す
				return;
			}

			auto* clock = system_->get_system<ClockSystem>();
			if (clock)
			{
				clock->start_clock();
			}

			if (
				auto* debug = system_->get_system<DebugSystem>();
				debug
				)
			{
				debug->debug_log("LoopManager run_normal()");
			}

			while (true)
			{
				system_->update_system();

				if (input->get_action_manager().get_action_state(
					InputAction::Esc) == ActionState::Down
					)
				{
					break;
				}

				if (clock)
				{
					loop_time += clock->get_delta_time();
					clock->wait_fixed_to_skip(5);
				}

				++loop_count;

			}
		}

		void run_window()
		{
			auto* window = system_->get_system<WindowsSystem>();
			if (!window)
			{
				return;
			}

			auto foucs_ = window->get_window_focus();

			auto* input = system_->get_system<InputSystem>();
			if (input)
			{
				//	Escバインド
				input->get_action_manager().add_action_bind(
					InputAction::Esc,
					InputKeyBoard::Esc
				);
			}

			auto* clock = system_->get_system<ClockSystem>();
			if (clock)
			{
				clock->start_clock();
			}

			auto* debug = system_->get_system<DebugSystem>();
			if (
				debug
				)
			{
				debug->debug_log("LoopManager run_window()");
			}

			while (true)
			{
				window->pull_window_event();
				if (window->is_window_closed())
				{
					break;
				}

				if (input)
				{
					if (
						input->get_action_manager().get_action_state(
							InputAction::Esc) == ActionState::Down
						)
					{
						window->shutdown_system();
						continue;
					}
				}
				
				auto foucs = window->get_window_focus();

				if (foucs_ != foucs) {
					foucs_ = foucs;
				}
				
				if (clock)
				{
					const auto& delta_time = clock->get_delta_time();
					loop_time += delta_time;
					clock->wait_fixed_to_skip(5);

					fps_time += delta_time;

					const auto second = ClockSystem::Milliseconds{ 1000 };

					if (fps_time >= second)
					{
						window->set_window_text(
							std::wstring{ L"FPS = " + std::to_wstring(fps_count) }.c_str()
						);
						fps_time -= second;
						fps_count = 0;
					}
				}

				if (foucs_) {
					system_->update_system();
				}

				++loop_count;
				++fps_count;
			}

			if (debug)
			{
				debug->debug_log("LoopManager loop_count = ", loop_count);
			}
		}

		SystemManager* system_{};

		ClockSystem::Milliseconds loop_time{};
		uint64_t loop_count{};

		ClockSystem::Milliseconds fps_time{};
		uint64_t fps_count{};
	};
}