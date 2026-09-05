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
			/// シザー短形ヘルパークラス
			/// </summary>
			class ScissorRectHelper final
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// シザー短形作成関数
				/// </summary>
				/// <details>
				/// 左上を [ 0,0 ] とした [ 描画クリッピング範囲 ] を決めれる構造体
				/// </details>
				/// <param name="right">[ X軸 ] 右側の値</param>
				/// <param name="bottom">[ Y軸 ] 下側の値</param>
				/// <param name="left">[ X軸 ] 左側の値</param>
				/// <param name="top">[ Y軸 ] 上側の値</param>
				/// <returns>作成されたシザー短形</returns>
				[[nodiscard]] static D3D12_RECT create_scissor_rect(long right, long bottom, long left = 0, long top = 0);

			private:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				ScissorRectHelper() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~ScissorRectHelper() = default;

			};
		}
	}
}