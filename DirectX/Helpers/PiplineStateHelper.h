#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassObject/PiplineState.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 補助名前空間
	/// </summary>
	namespace Helper {

		/// <summary>
		/// パイプラインステート補助クラス
		/// </summary>
		class PiplineStateHelper
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 取得関数 ===== */

			/* -- デフォルト関数 -- */

			/// <summary>
			/// デフォルトラスタライザー設定作成関数
			/// </summary>
			/// <returns>デフォルトラスタライザー設定</returns>
			[[nodiscard]] static D3D12_RASTERIZER_DESC default_rasterizer();

			/// <summary>
			/// デフォルトブレンド設定作成関数
			/// </summary>
			/// <returns>デフォルトブレンド設定</returns>
			[[nodiscard]] static D3D12_BLEND_DESC default_blend();

			/// <summary>
			/// デフォルトデプス設定作成関数
			/// </summary>
			/// <returns>デフォルトデプス設定</returns>
			[[nodiscard]] static D3D12_DEPTH_STENCIL_DESC default_depth();

			/* -- 有効化関数 -- */

			/// <summary>
			/// ブレンド有効化設定作成関数
			/// </summary>
			/// <returns>ブレンド有効化設定</returns>
			[[nodiscard]] static D3D12_BLEND_DESC enable_blend();

			/// <summary>
			/// デプス有効化設定作成関数
			/// </summary>
			/// <returns>デプス有効化設定</returns>
			[[nodiscard]] static D3D12_DEPTH_STENCIL_DESC enable_depth();

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			PiplineStateHelper() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~PiplineStateHelper() = default;

		};
	}
}