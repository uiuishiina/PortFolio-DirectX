#pragma once
#include<d3d12.h>

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
			/// ビューポートヘルパークラス
			/// </summary>
			class ViewportHelper final
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// ビューポート作成関数
				/// </summary>
				/// <details>
				/// [ NDC座標 ] を [ ピクセル座標 ] に変換するのに必要な情報構造体を作成する関数
				/// </details>
				/// <param name="width">ウィンドウの横幅</param>
				/// <param name="height">ウィンドウの縦幅</param>
				/// <param name="topX">起点となるX軸座標</param>
				/// <param name="topY">起点となるY軸座標</param>
				/// <param name="min_depth">最小深度値設定</param>
				/// <param name="max_depth">最大深度値設定</param>
				/// <returns>作成されたビューポート</returns>
				[[nodiscard]] static D3D12_VIEWPORT create_viewport(float width, float height,
					float topX = 0.0f, float topY = 0.0f, float min_depth = 0.0f, float max_depth = 1.0f);

			private:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				ViewportHelper() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~ViewportHelper() = default;

			};
		}
	}
}