#include "DrawCommands.h"

using namespace render::dx12;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 設定関数 -- */

/// <summary>
/// Beginコマンド設定関数
/// </summary>
/// <param name="func">追加するコマンド</param>
void command::DrawCommands::set_begin_command(const utility::DrawCommand& func) {
	begin_command = func;
}

/// <summary>
/// メイン描画コマンド追加関数
/// </summary>
/// <param name="func">追加するコマンド</param>
void command::DrawCommands::add_apply_command(const utility::DrawCommand& func) {
	apply_commands.push_back(func);
}

/// <summary>
/// Endコマンド設定関数
/// </summary>
/// <param name="func">追加するコマンド</param>
void command::DrawCommands::set_end_command(const utility::DrawCommand& func) {
	end_command = func;
}


/* -- 実行関数 -- */

/// <summary>
/// 描画パスBeginコマンド実行関数
/// </summary>
/// <param name="resouce">描画リソース構造体参照</param>
void command::DrawCommands::begin(resources::DrawResources& resouce) {
	begin_command(resouce);
}

/// <summary>
/// 描画パスメイン描画コマンド実行関数
/// </summary>
/// <param name="resouce">描画リソース構造体参照</param>
void command::DrawCommands::apply(resources::DrawResources& resouce) {
	for (auto& command : apply_commands) {
		command(resouce);
	}
}

/// <summary>
/// 描画パスEndコマンド実行関数
/// </summary>
/// <param name="resouce">描画リソース構造体参照</param>
void command::DrawCommands::end(resources::DrawResources& resouce) {
	end_command(resouce);
}