#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include"../../ClassObject/CommandList.h"

#include<memory>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// 描画オブジェクト基底クラス
		/// </summary>
		class DrawObjectBase : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DrawObjectBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~DrawObjectBase() = default;

			/* ===== 実行関数 ===== */

			/// <summary>
			/// オブジェクト描画純粋仮想関数
			/// </summary>
			/// <param name="list_">コマンドリスト参照</param>
			void virtual draw(
				ID3D12GraphicsCommandList* list_
			) const noexcept = 0;

		};
	}
}