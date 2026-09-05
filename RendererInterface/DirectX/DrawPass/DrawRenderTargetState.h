#pragma once
#include"../DrawResouces.h"
#include"Others/NonCopyableBase.h"
#include<vector>
#include<optional>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// 描画設定名前空間
		/// </summary>
		namespace state {

			/// <summary>
			/// 描画パス用レンダーターゲット設定クラス
			/// </summary>
			class DrawRenderTargetState final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DrawRenderTargetState() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~DrawRenderTargetState() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 設定関数 -- */

				/// <summary>
				/// 描画先設定追加関数
				/// </summary>
				/// <param name="slot">追加する描画先設定</param>
				void add_render_target_slot(RenderTargetSlot slot);

				/// <summary>
				/// デプスバッファ設定関数
				/// </summary>
				/// <param name="slot">設定するデプスバッファ設定</param>
				void set_depth(DepthSlot slot);


				/* -- 実行関数 -- */

				/// <summary>
				/// 描画パス実行時レンダーターゲットバインド関数
				/// </summary>
				/// <param name="resouce">描画リソース構造体参照</param>
				void apply(resources::DrawResources& resouce);

			private:
				/* ========== Privateメンバー関数 ========== */

				/// <summary>
				/// レンダーターゲット設定配列
				/// </summary>
				std::vector<RenderTargetSlot> render_targets_slot{};

				/// <summary>
				/// DepthBuffer設定
				/// </summary>
				std::optional<DepthSlot> depth_slot{};

			};
		}
	}
}