#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../DirectXContext.h"
#include"../Container/PassContainer.h"

#include"../Helpers/CommandPassDesc.h"
#include"../Helpers/PiplinePassDesc.h"

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

				std::vector<Resource::Pass::Commands::CommandPassDesc> command_pass{};

				/* -- Pipline -- */

				std::vector<Resource::Pass::Piplines::PiplinePassDesc> pipline_pass{};


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 
				/// </summary>
				/// <param name="name"></param>
				/// <param name="vector"></param>
				
				/// <summary>
				/// コマンドパス作成構造体補助関数
				/// </summary>
				/// <param name="name">コマンドパス名称</param>
				/// <param name="vector">コマンド配列</param>
				/// <param name="flag">描画パス呼び出しフラグ</param>
				void emplace_command_pass(
					std::string name,
					const std::vector<std::function<void(ClassModule::FrameContext&)>>& vector,
					bool flag
				) {

					command_pass.push_back({ name,vector,flag });
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

				/// <summary>
				/// パイプラインパス作成構造体補助関数
				/// </summary>
				/// <param name="name">パイプライン名称</param>
				/// <param name="desc">パイプラインパス外部参照補助構造体</param>
				/// <param name="flag">描画パス呼び出しフラグ</param>
				void emplace_pipline_pass(
					std::string name,
					Resource::Pass::Piplines::PiplinePassReference desc,
					bool flag
				) {

					pipline_pass.push_back({ name,desc,flag });
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
			/// <returns>呼び出せる描画パスリスト</returns>
			[[nodiscard]] static std::vector<std::string> initialize_pass(
				DirectXContext* context, 
				desc::PassDesc& desc
			) {

				std::vector<std::string> pass_list{};

				for (auto& [name, vec, flag] : desc.command_pass) {

					auto pass = std::make_unique<ClassModule::CommandPass>();
					pass->add_commands(vec);

					if (context->pass_container->add_pass(
						Container::PassKey{ name.c_str() },
						std::move(pass)
					)) {
						if (flag) {
							pass_list.push_back(name);
						}
					}
				}

				for (auto& [name, ref, flag] : desc.pipline_pass) {

					auto pass = Resource::Pass::Piplines::make_pipline_pass(context, ref);

					if (context->pass_container->add_pass(
						Container::PassKey{ name.c_str() },
						std::move(pass)
					)) {
						if (flag) {
							pass_list.push_back(name);
						}
					}
				}

				return pass_list;
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