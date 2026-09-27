#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassModule/PiplinePass.h"

#include"../Container/RootSignatureContainer.h"
#include"../Container/PiplineStateContainer.h"
#include"../Container/PassContainer.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// リソース名前空間
	/// </summary>
	namespace Resource {

		/// <summary>
		/// パス名前空間
		/// </summary>
		namespace Pass {

			/// <summary>
			/// パイプライン名前空間
			/// </summary>
			namespace Piplines {

				struct PiplinePassReference {

					/* ========== Publicメンバー変数 ========== */

					std::string root_name{};

					ClassModule::RootState root_state{};

					std::string pipline_name{};

					std::vector<std::string> command_pass_names{};

					/* ========== Publicメンバー関数 ========== */

					[[nodiscard]] std::unique_ptr<ClassModule::PiplinePass> set(
						DirectXContext* context_
					) {

						const auto root = context_->root_signature_container->get_root_signature(
							Container::RootSignatureKey{ root_name.c_str() }
						);
						const auto pipline = context_->pipline_state_container->get_pipline_state(
							Container::PiplineStateKey{ pipline_name.c_str() }
						);

						auto pass = std::make_unique<ClassModule::PiplinePass>(
							root,
							root_state,
							pipline
						);

						std::vector<ClassModule::PassBase*> commands{};

						for (auto& command_name : command_pass_names) {

							if (auto command = context_->pass_container->get_pass(
								Container::PassKey{ command_name.c_str() }
							); command) {

								commands.push_back(command);
							}
						}

						pass->add_command_passes(commands);

						return std::move(pass);
					}

				};

				using PiplinePassDesc = std::tuple<
					std::string,
					PiplinePassReference,
					bool
				>;
			}
		}
	}
}