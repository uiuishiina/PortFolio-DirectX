#pragma once

/* ========== Includeファイル ========== */

#include"Mesh.h"
#include"../TransformBuffer.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		class MeshObject : public DrawObjectBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			MeshObject() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~MeshObject() = default;

			/* ========== Privateメンバー変数 ========== */


			/* ===== 実行関数 ===== */

			/// <summary>
			/// メッシュ描画関数
			/// </summary>
			/// <param name="list_">コマンドリスト参照</param>
			void draw(
				ID3D12GraphicsCommandList* list_
			) const noexcept override {


			}


		};
	}
}