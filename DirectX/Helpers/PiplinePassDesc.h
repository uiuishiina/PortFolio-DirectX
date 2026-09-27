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

				/// <summary>
				/// パイプラインパス外部参照補助構造体
				/// </summary>
				struct PiplinePassReference {

					/* ========== Publicメンバー変数 ========== */

					/// <summary>
					/// ルートシグネチャー登録名
					/// </summary>
					std::string root_name{};

					/// <summary>
					/// ルートシグネチャー設定列挙体
					/// </summary>
					ClassModule::RootState root_state{};

					/// <summary>
					/// パイプラインステート登録名
					/// </summary>
					std::string pipline_name{};

					/// <summary>
					/// コマンドパス登録名配列
					/// </summary>
					std::vector<std::string> command_pass_names{};

				};

				/// <summary>
				/// パイプラインパス作成関数
				/// </summary>
				/// <param name="context_"></param>
				/// <param name="ref"></param>
				/// <returns></returns>
				[[nodiscard]] inline std::unique_ptr<ClassModule::PiplinePass> make_pipline_pass(
					DirectXContext* context_,
					PiplinePassReference& ref
				) {

					const auto root = context_->root_signature_container->get_root_signature(
						Container::RootSignatureKey{ ref.root_name.c_str() }
					);
					const auto pipline = context_->pipline_state_container->get_pipline_state(
						Container::PiplineStateKey{ ref.pipline_name.c_str() }
					);

					auto pass = std::make_unique<ClassModule::PiplinePass>(
						root,
						ref.root_state,
						pipline
					);

					std::vector<ClassModule::PassBase*> commands{};

					for (auto& command_name : ref.command_pass_names) {

						if (auto command = context_->pass_container->get_pass(
							Container::PassKey{ command_name.c_str() }
						); command) {

							commands.push_back(command);
						}
					}

					pass->add_command_passes(commands);

					return std::move(pass);
				}

				/// <summary>
				/// パイプラインパス設定定義
				/// </summary>
				using PiplinePassDesc = std::tuple<
					std::string,
					PiplinePassReference,
					bool
				>;
			}
		}
	}
}