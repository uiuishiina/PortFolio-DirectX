#include "DrawCommands.h"

using namespace render::dx12;

///====================================================================
/// 初期化関数
///====================================================================

//@param	=== Beginコマンド設定関数 ===
//@param	func	設定するコマンド
void command::DrawCommands::set_begin_command(const utility::DrawCommand& func) {
	begin_command = func;
}

//@brief	=== メイン描画コマンド追加関数 ===
//@param	func	追加するコマンド
void command::DrawCommands::add_apply_command(const utility::DrawCommand& func) {
	apply_commands.push_back(func);
}

//@param	=== Endコマンド設定関数 ===
//@param	func	設定するコマンド
void command::DrawCommands::set_end_command(const utility::DrawCommand& func) {
	end_command = func;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 描画パスBeginコマンド実行関数 ===
//@param	resouce	描画リソース
void command::DrawCommands::begin(resources::DrawResources& resouce) {
	begin_command(resouce);
}

//@brief	=== 描画パスメイン描画コマンド実行関数 ===
//@param	resouce	描画リソース
void command::DrawCommands::apply(resources::DrawResources& resouce) {
	for (auto& command : apply_commands) {
		command(resouce);
	}
}

//@brief	=== 描画パスEndコマンド実行関数 ===
//@param	resouce	描画リソース
void command::DrawCommands::end(resources::DrawResources& resouce) {
	end_command(resouce);
}