#include "ScissorRectHelper.h"

using namespace render::dx12::helper;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

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
[[nodiscard]] D3D12_RECT ScissorRectHelper::create_scissor_rect(long right, long bottom, long left, long top) {

	// シザー矩形作成
	D3D12_RECT scissorRect{};
	scissorRect.left	= left;
	scissorRect.top		= top;
	scissorRect.right	= right;
	scissorRect.bottom	= bottom;
	
	return scissorRect;
}