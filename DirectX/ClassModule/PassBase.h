#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"FrameContext.h"

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
		struct PassBase : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			PassBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~PassBase() = default;

			/* ===== 実行関数 ===== */

			/// <summary>
			/// 描画パス呼び出し純粋仮想関数
			/// </summary>
			/// <param name="context"></param>
			virtual void apply_pass(
				FrameContext& context
			) = 0;

		};
	}
}