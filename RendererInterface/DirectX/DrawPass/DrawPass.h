#pragma once
#include"DrawState.h"
#include"DrawRenderTargetState.h"
#include"DrawCommands.h"

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================
	
	namespace dx12 {

		///====================================================================
		/// DX12オブジェクト設定名前空間
		///====================================================================

		namespace desc {

			//@brief	=== 描画パス作成補助構造体 ===
			struct DrawPassDesc {

				//@brief	== 描画設定クラス参照 ==
				state::Drawstate* state_;

				//@brief	== 描画先設定クラス参照 ==
				state::DrawRenderTargetState* target_;

				//@breif	== 描画パスコマンドクラス参照 ==
				command::DrawCommands* command_;

				//@brief	== コンストラクタ ==
				DrawPassDesc() = default;
				DrawPassDesc(
					state::Drawstate* state,
					state::DrawRenderTargetState* target,
					command::DrawCommands* command
				) :state_(state), target_(target), command_(command) {};

			};
		};

		///====================================================================
		/// 描画パス名前空間
		///====================================================================

		namespace pass {

			///====================================================================
			/// DrawPass クラス
			///====================================================================

			//@brief	=== 描画パスクラス ===
			class DrawPass final : public NonMovableBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				DrawPass() = default;
				~DrawPass() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== 描画パス初期化関数 ===
				//@param	desc	描画パス作成補助構造体
				//@return	作成の成否
				[[nodiscard]] bool initialize_pass(desc::DrawPassDesc& desc);

				//@brief	=== 描画パス実行関数 ===
				//@param	resource	描画リソース
				void apply(resources::DrawResources& resource);

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== 描画設定クラス参照 ==
				state::Drawstate* draw_state{};

				//@brief	== 描画先設定クラス参照 ==
				state::DrawRenderTargetState* draw_target{};

				//@brief	== 描画コマンド設定クラス参照 ==
				command::DrawCommands* draw_commands{};

			};
		};
	};
};