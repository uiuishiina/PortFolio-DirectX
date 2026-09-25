#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"PassBase.h"

#include<functional>
#include<vector>
#include<span>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// 描画コマンドクラス
		/// </summary>
		struct CommandPass : PassBase
		{
			using Command = std::function<void(FrameContext&)>;
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			CommandPass() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~CommandPass() = default;

			/* ===== 実行関数 ===== */

			/// <summary>
			/// 描画パス呼び出し関数
			/// </summary>
			/// <param name="context"></param>
			void apply_pass(
				FrameContext& context
			) override {

				if (commands_.empty()) {
					return;
				}

				for (auto& c : commands_) {
					c(context);
				}
			}

			/// <summary>
			/// コマンド追加関数
			/// </summary>
			/// <param name="command">追加するコマンド</param>
			void add_command(
				const Command& command
			) {

				commands_.push_back(command);
			}

			/// <summary>
			/// コマンド配列追加関数
			/// </summary>
			/// <typeparam name="R">追加するコマンド配列型</typeparam>
			/// <param name="value">追加するコマンド配列</param>
			void add_commands(
				std::span<const Command> commands
			) {

				for (auto& v : commands) {
					add_command(v);
				}
			}

			/// <summary>
			/// コマンド全消去関数
			/// </summary>
			void claer_command() {

				commands_.clear();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			///	呼び出しコマンド配列
			/// </summary>
			std::vector<Command> commands_{};

		};
	}
}