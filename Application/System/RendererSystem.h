#pragma once

#include"System.h"
#include"DebugSystem.h"
#include"WindowsSystem.h"
#include"../../DirectX/DirectXRenderer.h"


/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

	struct CoreContext;
	struct ContainerContext;
}

namespace App
{
	class RendererSystem final : public ISystem
	{
	public:

		RendererSystem();
		~RendererSystem();

		bool init_system(SystemManager& manager) override;

		void update_system() override;

		void shutdown_system() override;

	private:

		DirectX::DirectXRenderer main_renderer{};

		WindowsSystem* main_window{};
		DebugSystem* debug_{};

		std::unique_ptr<DirectX::ContainerContext> container_context{};
		std::unique_ptr<DirectX::CoreContext> core_context{};

	};
}