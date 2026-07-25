#include "DrawPass.h"

///====================================================================
/// 初期化間数
///====================================================================

//@brief	=== 描画パス初期化関数 ===
//@param	state	描画設定クラス参照
//@param	target	描画先設定クラス参照
//@param	command	描画コマンド設定クラス参照
//@return	作成の成否
bool render::pass::DrawPass::initialize_pass(state::Drawstate* state, state::DrawRenderTargetState* target, command::DrawCommands* command) {

	//	すべてNullptrではないか確認
	if (state == nullptr || target == nullptr || command == nullptr) {
		return false;
	}

	//	設定
	draw_state = state;
	draw_target = target;
	draw_commands = command;

	return true;
}


///====================================================================
/// 実行時関数
///====================================================================

//@brief	=== 描画パス実行関数 ===
//@param	resouce	描画リソース
void render::pass::DrawPass::apply(render::resouces::DrawResouces& resouce)
{
	//	描画パス開始
	draw_commands->begin(resouce);

	//	描画先設定
	draw_target->apply(resouce);

	//	描画設定指定
	draw_state->apply(resouce);

	//	描画コマンド実行
	draw_commands->apply(resouce);

	//	描画パス終了
	draw_commands->end(resouce);
}