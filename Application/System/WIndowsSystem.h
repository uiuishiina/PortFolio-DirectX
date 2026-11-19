#pragma once

#include"System.h"
#include"../../Windows/Window.h"

/*
	既存のクラスをシステムで扱えるように中継するだけにする
*/

namespace App
{

	class WindowsSystem final : public ISystem
	{
	public:

		explicit WindowsSystem(
			const Windows::WindowSize& size
		) :
			size_{ size } {}

		bool init_system(SystemManager& manager) override
		{
			is_init = main_window.initialize_window(size_);

			return is_init;
		}

		void update_system() override
		{

		}

		void shutdown_system() override
		{
			if (is_init) { main_window.close_window(); }
		}

		void set_window_text(const wchar_t* text)
		{
			main_window.set_text(text);
		}

		void pull_window_event()
		{
			main_window.pull_event();
		}

		HWND get_hwnd() const noexcept
		{
			return main_window.get_hwnd();
		}

		Windows::WindowSize get_window_size() const noexcept
		{
			return main_window.get_size();
		}

		bool get_window_focus() const noexcept
		{
			return main_window.get_focus();
		}

		bool is_window_closed() const noexcept
		{
			return main_window.get_closed();
		}

	private:

		Windows::WindowSize size_{};

		Windows::Window main_window{};

	};
}