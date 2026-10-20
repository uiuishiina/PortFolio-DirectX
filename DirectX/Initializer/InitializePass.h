#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../DirectXContext.h"
#include"../Container/PassContainer.h"

#include"../Helpers/CommandPassDesc.h"
#include"../Helpers/PiplinePassDesc.h"
#include"../Helpers/DrawObjectPassDesc.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期化名前空間
	/// </summary>
	namespace Initialize {

		/// <summary>
		/// 設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// 描画パス設定構造体
			/// </summary>
			struct PassDesc {

				/* ========== Publicメンバー変数 ========== */

				/* -- Command -- */

				std::vector<Resource::Pass::Commands::CommandPassDesc> begin_pass{};

				std::vector<Resource::Pass::Commands::CommandPassDesc> command_pass{};

				std::vector<Resource::Pass::Commands::CommandPassDesc> end_pass{};

				/* -- DrawObject -- */

				std::vector<Resource::Pass::DrawObject::DrwObjectPassDesc> draw_object_pass{};

				/* -- Pipline -- */

				std::vector<Resource::Pass::Piplines::PiplinePassDesc> pipline_pass{};


				/* ========== Publicメンバー関数 ========== */

				void emplace_begin_pass(
					std::string name,
					const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector
				) {

					begin_pass.push_back({ name,vector });
				}

				void emplace_begin_pass(
					const Resource::Pass::Commands::CommandPassDesc& desc_
				) {

					begin_pass.push_back(desc_);
				}


				void emplace_end_pass(
					std::string name,
					const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector
				) {

					end_pass.push_back({ name,vector });
				}

				void emplace_end_pass(
					const Resource::Pass::Commands::CommandPassDesc& desc_
				) {

					end_pass.push_back(desc_);
				}

				/// <summary>
				/// コマンドパス作成構造体補助関数
				/// </summary>
				/// <param name="name">コマンドパス名称</param>
				/// <param name="vector">コマンド配列</param>
				/// <param name="flag">描画パス呼び出しフラグ</param>
				void emplace_command_pass(
					std::string name,
					const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector
				) {

					command_pass.push_back({ name,vector });
				}

				/// <summary>
				/// コマンドパス作成構造体補助関数オーバーロード
				/// </summary>
				/// <param name="desc_">事前作成した要素</param>
				void emplace_command_pass(
					const Resource::Pass::Commands::CommandPassDesc& desc_
				) {

					command_pass.push_back(desc_);
				}



				void emplace_draw_object_pass(
					std::string name,
					Resource::Pass::DrawObject::DrawObjectPassReference desc
				) {

					draw_object_pass.push_back({ name,desc });
				}

				void emplace_draw_object_pass(
					const Resource::Pass::DrawObject::DrwObjectPassDesc& desc_
				) {

					draw_object_pass.push_back(desc_);
				}


				/// <summary>
				/// パイプラインパス作成構造体補助関数
				/// </summary>
				/// <param name="name">パイプライン名称</param>
				/// <param name="desc">パイプラインパス外部参照補助構造体</param>
				/// <param name="flag">描画パス呼び出しフラグ</param>
				void emplace_pipline_pass(
					std::string name,
					Resource::Pass::Piplines::PiplinePassReference desc
				) {

					pipline_pass.push_back({ name,desc });
				}

				/// <summary>
				/// コマンドパス作成構造体補助関数オーバーロード
				/// </summary>
				/// <param name="desc_">事前作成した要素</param>
				void emplace_pipline_pass(
					const Resource::Pass::Piplines::PiplinePassDesc& desc_
				) {

					pipline_pass.push_back(desc_);
				}
				
			};
		}

		/// <summary>
		/// 描画パス初期化クラス
		/// </summary>
		class InitializePass
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 初期化関数 ===== */
			
			/// <summary>
			/// 描画パス初期化関数
			/// </summary>
			/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
			/// <param name="desc">描画パス設定構造体参照</param>
			static void initialize_pass(
				DirectXContext* context, 
				desc::PassDesc& desc
			) {

				std::vector<std::string> pass_list{};

				/* ===== Begin ===== */

				for (auto& [name, vec] : desc.begin_pass) {

					//	インスタンス作成
					auto pass = std::make_unique<ClassModule::CommandPass>();

					//	コマンド追加
					pass->add_commands(vec);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PassKey{ name.c_str() },
						std::move(pass)
					)) {
						pass_list.push_back(name);
					}
				}

				/* ===== Command ===== */

				for (auto& [name, vec] : desc.command_pass) {

					//	インスタンス作成
					auto pass = std::make_unique<ClassModule::CommandPass>();

					//	コマンド追加
					pass->add_commands(vec);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PassKey{ name.c_str() },
						std::move(pass)
					)) {
						pass_list.push_back(name);
					}
				}

				/* ===== DrawObject ===== */

				for (auto& [name, ref] : desc.draw_object_pass) {

					//	インスタンス作成
					auto pass = std::make_unique<ClassModule::DrawObjectPass>();

					//	描画オブジェクト参照配列
					std::vector<ClassModule::DrawObjectBase*> objs{};

					//	配列にオブジェクトを追加
					for (auto& obj_name : ref.draw_object_names) {

						if (auto obj = context->draw_object_container->get_draw_object(
							Container::DrawObjectKey{ obj_name.c_str() }
						); obj) {

							objs.push_back(obj);
						}
					}

					//	配列設定
					pass->add_objects(objs);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PassKey{ name.c_str() },
						std::move(pass)
					)) {
						pass_list.push_back(name);
					}
				}

				/* ===== Pipline ===== */

				for (auto& [name, ref] : desc.pipline_pass) {

					//	各インスタンス参照取得
					const auto root = context->root_signature_container->get_root_signature(
						Container::RootSignatureKey{ ref.root_name.c_str() }
					);
					const auto pipline = context->pipline_state_container->get_pipline_state(
						Container::PiplineStateKey{ ref.pipline_name.c_str() }
					);

					//	インスタンス作成
					auto pass = std::make_unique<ClassModule::PiplinePass>(
						root,
						ref.root_state,
						pipline
					);

					//	パス参照配列作成
					std::vector<ClassModule::PassBase*> passes{};

					//	配列にパスを追加
					for (auto& pass_name : ref.pass_names) {

						if (auto command = context->pass_container->get_pass(
							Container::PassKey{ pass_name.c_str() }
						); command) {

							passes.push_back(command);
						}
					}

					//	設定追加
					pass->add_command_passes(passes);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PassKey{ name.c_str() },
						std::move(pass)
					)) {
						pass_list.push_back(name);
					}
				}

				/* ===== End ===== */

				for (auto& [name, vec] : desc.end_pass) {

					//	インスタンス作成
					auto pass = std::make_unique<ClassModule::CommandPass>();

					//	コマンド追加
					pass->add_commands(vec);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PassKey{ name.c_str() },
						std::move(pass)
					)) {
						pass_list.push_back(name);
					}
				}

				DEBUG_LOG(
					HandyItems::Debug::const_str::LineBreak,
					"========== CreatePassName =========="
				);
				auto passCount = 0;

				for (auto& name : pass_list) {
					
					DEBUG_LOG(++passCount, " = ", name);
				}

			}

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializePass() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~InitializePass() = default;

		};
	}
}