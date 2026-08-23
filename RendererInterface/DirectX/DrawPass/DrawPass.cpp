#include "DrawPass.h"

using namespace render::dx12::pass;

///====================================================================
/// 初期化間数
///====================================================================

//@brief	=== 描画パス初期化関数 ===
//@param	desc	描画パス作成補助構造体
//@return	作成の成否
[[nodiscard]] bool DrawPass::initialize_pass(desc::DrawPassDesc& desc) {

	//	すべてNullptrではないか確認
	if (desc.state_ == nullptr || desc.target_ == nullptr || desc.command_ == nullptr) {
		return false;
	}

	//	設定
	draw_state = desc.state_;
	draw_target = desc.target_;
	draw_commands = desc.command_;

	return true;
}


///====================================================================
/// 実行時関数
///====================================================================

//@brief	=== 描画パス実行関数 ===
//@param	resouce	描画リソース
void DrawPass::apply(resources::DrawResources& resource)
{
	//	描画パス開始
	draw_commands->begin(resource);

	//	描画先設定
	draw_target->apply(resource);

	//	描画設定指定
	draw_state->apply(resource);

	//	描画コマンド実行
	draw_commands->apply(resource);

	//	描画パス終了
	draw_commands->end(resource);
}