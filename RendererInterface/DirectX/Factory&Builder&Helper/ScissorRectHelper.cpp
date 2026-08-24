#include "ScissorRectHelper.h"

using namespace render::dx12::helper;

//@brief	=== シザー短形作成関数 ===
//@details	左上を [ 0,0 ] とした [ 描画クリッピング範囲 ] を決めれる構造体
//@param	right	[ X軸 ] 右側の値
//@param	bottom	[ Y軸 ] 下側の値
//@param	left	[ X軸 ] 左側の値
//@param	top		[ Y軸 ] 上側の値
//@return	作成されたシザー短形
[[nodiscard]] D3D12_RECT ScissorRectHelper::create_scissor_rect(long right, long bottom, long left, long top) {

	// シザー矩形作成
	D3D12_RECT scissorRect{};
	scissorRect.left	= left;
	scissorRect.top		= top;
	scissorRect.right	= right;
	scissorRect.bottom	= bottom;
	
	return scissorRect;
}