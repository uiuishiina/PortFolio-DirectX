#include "ViewportHelper.h"

using namespace render::dx12::helper;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

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
[[nodiscard]] D3D12_VIEWPORT ViewportHelper::create_viewport(float width, float height,
	float topX, float topY, float min_depth, float max_depth) {

	// ビューポート作成
	D3D12_VIEWPORT viewport{};
	viewport.TopLeftX	= topX;
	viewport.TopLeftY	= topY;
	viewport.Width		= width;
	viewport.Height		= height;
	viewport.MinDepth	= min_depth;
	viewport.MaxDepth	= max_depth;
	
	return viewport;
}