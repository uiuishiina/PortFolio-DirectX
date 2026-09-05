#include "DrawPass.h"

using namespace render::dx12::pass;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// 描画パス初期化関数
/// </summary>
/// <param name="desc">描画パス作成補助構造体</param>
/// <returns>初期化の成否</returns>
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


/// <summary>
/// 描画パス実行関数
/// </summary>
/// <param name="resource">描画リソース構造体参照</param>
void DrawPass::apply(resources::DrawResources& resource) {

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