#pragma once
#include"DrawCommands.h"
#include"PassBase.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクト設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// コマンドパス作成補助構造体
			/// </summary>
			struct CommandPassDesc {

				/// <summary>
				/// 描画パスコマンドクラス参照
				/// </summary>
				command::DrawCommands* command_;

				/// <summary>
				/// コンストラクタ
				/// </summary>
				CommandPassDesc() = default;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="command">描画パスコマンドクラス参照</param>
				CommandPassDesc(command::DrawCommands* command) :
					command_{ command } {};

			};
		}

		/// <summary>
		/// 描画パス名前空間
		/// </summary>
		namespace pass {

			/// <summary>
			/// コマンドパスクラス
			/// </summary>
			class CommandPass final : public PassBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				CommandPass() = default;

				/// <summary>
				/// コンストラクタ
				/// </summary>
				~CommandPass() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// コマンドパス初期化関数
				/// </summary>
				/// <param name="desc">コマンドパス作成補助構造体</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] bool initialize_pass(desc::CommandPassDesc& desc);

				/// <summary>
				/// コマンドパス実行関数
				/// </summary>
				/// <param name="resource">描画リソース構造体参照</param>
				void apply(resources::DrawResources& resource) override;

			private:
				/* ========== Privateメンバー関数 ========== */

				/// <summary>
				/// コマンドパスコマンド設定クラス参照
				/// </summary>
				command::DrawCommands* draw_commands{};

			};
		}
	}
}