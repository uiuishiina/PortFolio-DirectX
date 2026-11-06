#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../FrameContext.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// 描画パス基底クラス
		/// </summary>
		class PathBase : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~PathBase() = default;

			/* ===== 実行関数 ===== */

			/// <summary>
			/// 描画パス呼び出し純粋仮想関数
			/// </summary>
			/// <param name="context"></param>
			virtual void apply_path(
				FrameContext& context
			) = 0;

		};
	}
}