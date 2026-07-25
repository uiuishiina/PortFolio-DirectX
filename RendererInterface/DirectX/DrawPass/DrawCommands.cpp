#include "DrawCommands.h"

using namespace render::dx12;

///====================================================================
/// 初期化関数
///====================================================================

//@param	=== Beginコマンド設定関数 ===
//@param	func	設定するコマンド
void command::DrawCommands::set_begin_command(const std::function<void(resouces::DrawResouces&)>& func) {
	begin_command = func;
}

//@brief	=== 描画コマンド追加関数 ===
//@param	func	追加するコマンド
void command::DrawCommands::add_apply_command(const std::function<void(resouces::DrawResouces&)>& func) {
	apply_commands.push_back(func);
}

//@param	=== Endコマンド設定関数 ===
//@param	func	設定するコマンド
void command::DrawCommands::set_end_command(const std::function<void(resouces::DrawResouces&)>& func) {
	end_command = func;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 描画パス実行時Beginコマンド実行関数 ===
//@param	resouce	描画リソース
void command::DrawCommands::begin(resouces::DrawResouces& resouce) {
	begin_command(resouce);
}

//@brief	=== 描画パス実行時描画コマンド実行関数 ===
//@param	resouce	描画リソース
void command::DrawCommands::apply(resouces::DrawResouces& resouce) {
	for (auto& command : apply_commands) {
		command(resouce);
	}
}

//@brief	=== 描画パス実行時Endコマンド実行関数 ===
//@param	resouce	描画リソース
void command::DrawCommands::end(resouces::DrawResouces& resouce) {
	end_command(resouce);
}