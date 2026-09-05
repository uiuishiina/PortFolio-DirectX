#pragma once
#include"Others/NonCopyableBase.h"
#include"../DrawResouces.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// 描画パス名前空間
		/// </summary>
		namespace pass {

			/// <summary>
			/// 描画パスクラス
			/// </summary>
			class PassBase : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				PassBase() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~PassBase() = default;


				/* ========== 純粋仮想関数 ========== */

				/// <summary>
				/// 描画パス実行関数
				/// </summary>
				/// <param name="resource">描画リソース構造体参照</param>
				virtual void apply(resources::DrawResources& resource) = 0;

			};
		}
	}
}