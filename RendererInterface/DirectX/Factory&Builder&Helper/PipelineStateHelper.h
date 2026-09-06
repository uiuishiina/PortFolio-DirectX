#pragma once
#include"../DirectXobject/PipelineState.h"
#include"../AddFile/d3dx12.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// Helper名前空間
		/// </summary>
		namespace helper {

			/// <summary>
			/// パイプラインステートヘルパークラス
			/// </summary>
			class PipelineStateHelper final
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// ブレンド有効化設定作成関数
				/// </summary>
				/// <returns>ブレンド有効化設定</returns>
				[[nodiscard]] static D3D12_BLEND_DESC get_enable_blend();

				/// <summary>
				/// デプス有効化設定作成関数
				/// </summary>
				/// <returns>デプス有効化設定</returns>
				[[nodiscard]] static D3D12_DEPTH_STENCIL_DESC get_enable_depth();

			private:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				PipelineStateHelper() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~PipelineStateHelper() = default;

			};
		}
	}
}