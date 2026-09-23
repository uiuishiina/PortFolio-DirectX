#pragma once

/* ========== Includeファイル ========== */

#include"../ClassModule/CommandPass.h"

#include<vector>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {


	[[nodiscard]] inline std::pair<
		std::unique_ptr<ClassModule::PassBase>,
		std::string
	> make_command_pass(
		std::string name,
		const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector
	) {

		auto pass = std::make_unique<ClassModule::CommandPass>();
		pass->add_commands(vector);

		return { std::move(pass), name };
	}


	namespace Resource {

		using Command = std::function<void(ClassModule::FrameContext&)>;

		const Command Test = [](ClassModule::FrameContext& frame) {
			auto* back = frame.back_buffer;
			back->barrier_transition(frame.graphic_list->get(), D3D12_RESOURCE_STATE_RENDER_TARGET);

			float color[4] = { 1,1,1,1 };
			frame.graphic_list->get()->ClearRenderTargetView(back->get_RTV_handle(), color, 0, nullptr);

			back->barrier_transition(frame.graphic_list->get(), D3D12_RESOURCE_STATE_PRESENT);
			};


	}
}