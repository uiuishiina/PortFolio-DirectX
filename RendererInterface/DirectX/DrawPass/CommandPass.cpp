#include "CommandPass.h"

using namespace render::dx12::pass;

//@brief	=== コマンドパス初期化関数 ===
//@param	desc	コマンドパス作成補助構造体
//@return	作成の成否
[[nodiscard]] bool CommandPass::initialize_pass(render::dx12::desc::CommandPassDesc& desc) {

	if (desc.command_ == nullptr) {
		return false;
	}

	draw_commands = desc.command_;

	return true;
}

//@brief	=== コマンドパス実行関数 ===
//@param	resource	描画リソース
void CommandPass::apply(resources::DrawResources& resource) {

	//	コマンドパス開始
	draw_commands->begin(resource);

	//	コマンドパスコマンド実行
	draw_commands->apply(resource);

	//	コマンドパス終了
	draw_commands->end(resource);
}