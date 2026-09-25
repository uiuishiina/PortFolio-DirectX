#pragma once

/* ========== Includeファイル ========== */

#include"../ClassModule/CommandPass.h"

#include<vector>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// コマンドパス作成構造体補助関数
	/// </summary>
	/// <param name="name">コマンドパス名称</param>
	/// <param name="vector">コマンド配列</param>
	/// <returns>作成したコマンドパス</returns>
	[[nodiscard]] inline std::pair<
		std::string,
		std::unique_ptr<ClassModule::PassBase>
	> make_command_pass(
		std::string name,
		const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector
	) {

		auto pass = std::make_unique<ClassModule::CommandPass>();
		pass->add_commands(vector);

		return { name,std::move(pass) };
	}

	/// <summary>
	/// リソース名前空間
	/// </summary>
	namespace Resource {

		/// <summary>
		/// パス名前空間
		/// </summary>
		namespace Pass {

			/// <summary>
			/// コマンド名前空間
			/// </summary>
			namespace Commands {

				/* ===== 単体コマンド ===== */

				using Command = std::function<void(ClassModule::FrameContext&)>;

				/// <summary>
				/// バックバッファ用名前空間
				/// </summary>
				namespace BackBuffer {

					/* ===== バリア遷移 ===== */

					const Command TransitionTarget = [](ClassModule::FrameContext& frame) {

						frame.back_buffer->barrier_transition(
							frame.graphic_list->get(),
							D3D12_RESOURCE_STATE_RENDER_TARGET
						); };

					const Command TransitionPresent = [](ClassModule::FrameContext& frame) {

						frame.back_buffer->barrier_transition(
							frame.graphic_list->get(),
							D3D12_RESOURCE_STATE_PRESENT
						); };

					/* ===== クリア ===== */

					const Command ClearBlack = [](ClassModule::FrameContext& frame) {

						float color[4] = { 0,0,0,1 };
						frame.graphic_list->get()->ClearRenderTargetView(
							frame.back_buffer->get_RTV_handle(),
							color,
							0,
							nullptr
						); };

					const Command ClearRed = [](ClassModule::FrameContext& frame) {

						float color[4] = { 1,0,0,1 };
						frame.graphic_list->get()->ClearRenderTargetView(
							frame.back_buffer->get_RTV_handle(),
							color,
							0,
							nullptr
						); };

					const Command ClearGreen = [](ClassModule::FrameContext& frame) {

						float color[4] = { 0,1,0,1 };
						frame.graphic_list->get()->ClearRenderTargetView(
							frame.back_buffer->get_RTV_handle(),
							color,
							0,
							nullptr
						); };

					const Command ClearBlue = [](ClassModule::FrameContext& frame) {

						float color[4] = { 0,0,1,1 };
						frame.graphic_list->get()->ClearRenderTargetView(
							frame.back_buffer->get_RTV_handle(),
							color,
							0,
							nullptr
						); };

					const Command ClearWhite = [](ClassModule::FrameContext& frame) {

						float color[4] = { 1,1,1,1 };
						frame.graphic_list->get()->ClearRenderTargetView(
							frame.back_buffer->get_RTV_handle(),
							color,
							0,
							nullptr
						); };


					/* ===== セット ===== */

					const Command Set = [](ClassModule::FrameContext& frame) {

						D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle[] = { frame.back_buffer->get_RTV_handle() };

						frame.graphic_list->get()->OMSetRenderTargets(
							1,
							rtv_handle,
							false,
							nullptr
						); };

				}


				/* ===== コマンド配列 ===== */

				const std::vector<
					std::function<void(ClassModule::FrameContext&)>
				> Begin = {
					BackBuffer::TransitionTarget,
					BackBuffer::Set
				};

				const std::vector<
					std::function<void(ClassModule::FrameContext&)>
				> End = {
					BackBuffer::TransitionPresent
				};

			}
		}
	}
}