#pragma once

#include"System.h"
#include"WindowsSystem.h"
#include"../../DirectX/DirectXRenderer.h"

namespace App
{
	class RendererSystem final : public ISystem
	{
	public:


		bool init_system(SystemManager& manager) override
		{
			auto* window = manager.get_system<WindowsSystem>();
			if (!window)
			{
				return is_init;
			}
			if (!window->is_initialize())
			{
				return is_init;
			}

			if (!main_renderer.initialize_renderer(
				window->get_hwnd(),
				window->get_window_size().width_,
				window->get_window_size().height_
			))
			{
				return is_init;
			}

			is_init = true;
			return is_init;
		}

		void update_system() override
		{
			main_renderer.update_renderer();
		}

		void shutdown_system() override
		{
			if (is_init)
			{
				main_renderer.end_renderer();
			}
		}

	private:

		DirectX::DirectXRenderer main_renderer{};
	};

}