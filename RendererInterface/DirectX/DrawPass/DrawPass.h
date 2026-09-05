#pragma once
#include"DrawState.h"
#include"DrawRenderTargetState.h"
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
			/// 描画パス作成補助構造体
			/// </summary>
			struct DrawPassDesc {

				/// <summary>
				/// 描画設定クラス参照
				/// </summary>
				state::Drawstate* state_;

				/// <summary>
				/// 描画先設定クラス参照
				/// </summary>
				state::DrawRenderTargetState* target_;

				/// <summary>
				/// 描画パスコマンドクラス参照
				/// </summary>
				command::DrawCommands* command_;

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DrawPassDesc() = default;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="state">描画設定クラス参照</param>
				/// <param name="target">描画先設定クラス参照</param>
				/// <param name="command">描画パスコマンドクラス参照</param>
				DrawPassDesc(
					state::Drawstate* state,
					state::DrawRenderTargetState* target,
					command::DrawCommands* command
				) :state_{ state }, target_{ target }, command_{ command } {};

			};
		}

		/// <summary>
		/// 描画パス名前空間
		/// </summary>
		namespace pass {

			/// <summary>
			/// 描画パスクラス
			/// </summary>
			class DrawPass final : public PassBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DrawPass() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~DrawPass() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 描画パス初期化関数
				/// </summary>
				/// <param name="desc">描画パス作成補助構造体</param>
				/// <returns>初期化の成否</returns>
				[[nodiscard]] bool initialize_pass(desc::DrawPassDesc& desc);

				/// <summary>
				/// 描画パス実行関数
				/// </summary>
				/// <param name="resource">描画リソース構造体参照</param>
				void apply(resources::DrawResources& resource) override;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// 描画設定クラス参照
				/// </summary>
				state::Drawstate* draw_state{};

				/// <summary>
				/// 描画先設定クラス参照
				/// </summary>
				state::DrawRenderTargetState* draw_target{};

				/// <summary>
				/// 描画コマンド設定クラス参照
				/// </summary>
				command::DrawCommands* draw_commands{};

			};
		}
	}
}