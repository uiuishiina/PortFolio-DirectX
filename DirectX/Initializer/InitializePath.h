#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../DirectXContext.h"
#include"../Container/PassContainer.h"

#include"../Helpers/CommandPathDesc.h"
#include"../Helpers/PiplinePathDesc.h"
#include"../Helpers/DrawObjectPathDesc.h"

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
			struct PathDesc {

				/* ========== Publicメンバー変数 ========== */

				/* -- Command -- */

				std::vector<Resource::Path::Commands::CommandPathDesc> begin_pass{};

				std::vector<Resource::Path::Commands::CommandPathDesc> command_pass{};

				std::vector<Resource::Path::Commands::CommandPathDesc> end_pass{};

				/* -- DrawObject -- */

				std::vector<Resource::Path::DrawObject::DrwObjectPathDesc> draw_object_pass{};

				/* -- Pipline -- */

				std::vector<Resource::Path::Piplines::PiplinePathDesc> pipline_pass{};


				/* ========== Publicメンバー関数 ========== */

				void emplace_begin_path(
					std::string name,
					const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector
				) {

					begin_pass.push_back({ name,vector });
				}

				void emplace_begin_path(
					const Resource::Path::Commands::CommandPathDesc& desc_
				) {

					begin_pass.push_back(desc_);
				}


				void emplace_end_path(
					std::string name,
					const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector
				) {

					end_pass.push_back({ name,vector });
				}

				void emplace_end_path(
					const Resource::Path::Commands::CommandPathDesc& desc_
				) {

					end_pass.push_back(desc_);
				}

				/// <summary>
				/// コマンドパス作成構造体補助関数
				/// </summary>
				/// <param name="name">コマンドパス名称</param>
				/// <param name="vector">コマンド配列</param>
				/// <param name="flag">描画パス呼び出しフラグ</param>
				void emplace_command_path(
					std::string name,
					const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector
				) {

					command_pass.push_back({ name,vector });
				}

				/// <summary>
				/// コマンドパス作成構造体補助関数オーバーロード
				/// </summary>
				/// <param name="desc_">事前作成した要素</param>
				void emplace_command_path(
					const Resource::Path::Commands::CommandPathDesc& desc_
				) {

					command_pass.push_back(desc_);
				}



				void emplace_draw_object_path(
					std::string name,
					Resource::Path::DrawObject::DrawObjectPathReference desc
				) {

					draw_object_pass.push_back({ name,desc });
				}

				void emplace_draw_object_path(
					const Resource::Path::DrawObject::DrwObjectPathDesc& desc_
				) {

					draw_object_pass.push_back(desc_);
				}


				/// <summary>
				/// パイプラインパス作成構造体補助関数
				/// </summary>
				/// <param name="name">パイプライン名称</param>
				/// <param name="desc">パイプラインパス外部参照補助構造体</param>
				/// <param name="flag">描画パス呼び出しフラグ</param>
				void emplace_pipline_path(
					std::string name,
					Resource::Path::Piplines::PiplinePathReference desc
				) {

					pipline_pass.push_back({ name,desc });
				}

				/// <summary>
				/// コマンドパス作成構造体補助関数オーバーロード
				/// </summary>
				/// <param name="desc_">事前作成した要素</param>
				void emplace_pipline_path(
					const Resource::Path::Piplines::PiplinePathDesc& desc_
				) {

					pipline_pass.push_back(desc_);
				}
				
			};
		}

		/// <summary>
		/// 描画パス初期化クラス
		/// </summary>
		class InitializePath
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 初期化関数 ===== */
			
			/// <summary>
			/// 描画パス初期化関数
			/// </summary>
			/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
			/// <param name="desc">描画パス設定構造体参照</param>
			static void initialize_path(
				DirectXContext* context, 
				const desc::PathDesc& desc
			) {

				std::vector<std::string> path_list{};

				/* ===== Begin ===== */

				for (auto& [name, vec] : desc.begin_pass) {

					//	インスタンス作成
					auto path = std::make_unique<ClassModule::CommandPath>();

					//	コマンド追加
					path->add_commands(vec);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PathKey{ name.c_str() },
						std::move(path)
					)) {
						path_list.push_back(name);
					}
				}

				/* ===== Command ===== */

				for (auto& [name, vec] : desc.command_pass) {

					//	インスタンス作成
					auto path = std::make_unique<ClassModule::CommandPath>();

					//	コマンド追加
					path->add_commands(vec);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PathKey{ name.c_str() },
						std::move(path)
					)) {
						path_list.push_back(name);
					}
				}

				/* ===== DrawObject ===== */

				for (auto& [name, ref] : desc.draw_object_pass) {

					//	インスタンス作成
					auto path = std::make_unique<ClassModule::DrawObjectPath>();

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
					path->add_objects(objs);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PathKey{ name.c_str() },
						std::move(path)
					)) {
						path_list.push_back(name);
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
					auto path = std::make_unique<ClassModule::PiplinePath>(
						root,
						ref.root_state,
						pipline
					);

					//	パス参照配列作成
					std::vector<ClassModule::PathBase*> passes{};

					//	配列にパスを追加
					for (auto& pass_name : ref.pass_names) {

						if (auto command = context->pass_container->get_pass(
							Container::PathKey{ pass_name.c_str() }
						); command) {

							passes.push_back(command);
						}
					}

					//	設定追加
					path->add_command_paths(passes);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PathKey{ name.c_str() },
						std::move(path)
					)) {
						path_list.push_back(name);
					}
				}

				/* ===== End ===== */

				for (auto& [name, vec] : desc.end_pass) {

					//	インスタンス作成
					auto path = std::make_unique<ClassModule::CommandPath>();

					//	コマンド追加
					path->add_commands(vec);

					//	コンテナに追加
					if (context->pass_container->add_pass(
						Container::PathKey{ name.c_str() },
						std::move(path)
					)) {
						path_list.push_back(name);
					}
				}

				DEBUG_LOG(
					HandyItems::Debug::const_str::LineBreak,
					"========== CreatePassName =========="
				);
				auto passCount = 0;

				for (auto& name : path_list) {
					
					DEBUG_LOG(++passCount, " = ", name);
				}

			}

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializePath() = default;

		};
	}
}