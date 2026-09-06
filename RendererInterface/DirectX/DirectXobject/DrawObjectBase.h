#pragma once
#include"Others/NonCopyableBase.h"
#include"GraphicsCommandList.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// 描画オブジェクト名前空間
		/// </summary>
		namespace drawobject {

			/// <summary>
			/// 描画オブジェクト基底クラス
			/// </summary>
			class DrawObjectBase : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DrawObjectBase() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~DrawObjectBase() = default;


				/* ========== Publicメンバー関数 ========== */
			
				/// <summary>
				/// オブジェクト描画純粋仮想関数
				/// </summary>
				/// <param name="list">描画用コマンドリスト参照</param>
				virtual void draw(ID3D12GraphicsCommandList* list) const noexcept = 0;

			};
		}
	}
}