#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../../ClassObject/PiplineState.h"
#include"../../ClassObject/RootSignature.h"
#include"CommandPath.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// ルートシグネチャー設定列挙体
		/// </summary>
		enum class RootState {
			Compute,
			Graphics
		};

		/// <summary>
		/// パイプラインパスクラス
		/// </summary>
		class PiplinePath : public PathBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="root">ルートシグネチャー参照</param>
			/// <param name="state">ルートシグネチャー設定列挙体</param>
			/// <param name="pipline">パイプラインステート参照</param>
			explicit PiplinePath(
				ClassObject::RootSignature* root,
				RootState state,
				ClassObject::PiplineState* pipline
			) :
				root_{ root },
				root_state{ state },
				pipline_state{ pipline } {}

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// コマンドパス配列追加関数
			/// </summary>
			/// <typeparam name="R">追加するコマンドパス配列型</typeparam>
			/// <param name="value">追加するコマンドパス配列</param>
			void add_command_paths(
				const std::span<PathBase*> paths
			) {

				for (auto& pass : paths) {
					command_passes.push_back(pass);
				}
			}

			/// <summary>
			/// コマンドパス全消去関数
			/// </summary>
			void claer_command() {

				command_passes.clear();
			}


			/* ===== 実行関数 ===== */

			/// <summary>
			/// 描画パス呼び出し関数
			/// </summary>
			/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
			void apply_path(
				FrameContext& context
			) override {

				set_state(context);

				for (auto& pass : command_passes) {
					pass->apply_path(context);
				}
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ルートシグネチャー参照
			/// </summary>
			ClassObject::RootSignature* root_{};

			/// <summary>
			/// ルートシグネチャー設定列挙体
			/// </summary>
			RootState root_state{};

			/// <summary>
			/// パイプラインステート参照
			/// </summary>
			ClassObject::PiplineState* pipline_state{};

			/// <summary>
			///	呼び出しコマンド配列
			/// </summary>
			std::vector<PathBase*> command_passes{};

			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// 設定関数
			/// </summary>
			/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
			void set_state(
				FrameContext& context
			) {

				if (root_state == RootState::Compute) {
					context.graphic_list->get()->SetComputeRootSignature(root_->get());
				}
				else {
					context.graphic_list->get()->SetGraphicsRootSignature(root_->get());
				}
				
				context.graphic_list->get()->SetPipelineState(pipline_state->get());
			}

		};
	}
}