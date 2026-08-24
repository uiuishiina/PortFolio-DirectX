#include "ViewportHelper.h"

using namespace render::dx12::helper;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== ビューポート作成関数 ===
//@details	[ NDC座標 ] を [ ピクセル座標 ] に変換するのに必要な情報構造体を作成する関数
//@param	width	ウィンドウの横幅
//@param	height	ウィンドウの縦幅
//@param	topX	起点となるX軸座標
//@param	topY	起点となるY軸座標
//@param	min_depth	最小深度値設定
//@param	max_depth	最大深度値設定
//@return	作成されたビューポート
[[nodiscard]] D3D12_VIEWPORT ViewportHelper::create_viewport(float width, float height,
	float topX, float topY, float min_depth, float max_depth) {

	// ビューポート作成
	D3D12_VIEWPORT viewport{};
	viewport.TopLeftX	= topX;
	viewport.TopLeftY	= topY;
	viewport.Width		= width;
	viewport.Height		= height;
	viewport.MinDepth	= min_depth;
	viewport.MaxDepth	= 1.0f;
	
	return viewport;
}