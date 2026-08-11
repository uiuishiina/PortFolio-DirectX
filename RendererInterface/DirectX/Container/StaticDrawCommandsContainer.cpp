#include "StaticDrawCommandsContainer.h"
#include"../../../Debug/DebugLogSystem.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 単体コマンド追加関数 ===
//@param	name	追加するコマンド名
//@return	追加の成否
[[nodiscard]] bool StaticDrawCommandsContainer::add_command_map(const std::string& name, const utility::DrawCommand& func) {

	//	登録済みか確認
	const auto it = command_list.find(name);
	if (it != command_list.end()) {
		return false;
	}

	command_list.emplace(name, func);
	return true;
}

//@breif	=== 描画パスコマンド作成関数 ===
//@param	key_name	登録するキーの名前
//@param	desc		描画パスコマンド作成構造体
//@return	作成の成否
[[nodiscard]] bool StaticDrawCommandsContainer::create_draw_commands(const std::string& key_name, desc::DrawCommandDesc& desc) {

	//	すでに同名で登録されているなら登録失敗
	auto hash = get_hash_key(key_name);
	if (hash.has_value()) {
		return false;
	}

	//	インスタンス生成
	auto commands = std::make_unique<command::DrawCommands>();

	//	Beginコマンド設定
	if (!desc.begin_name.empty()) {
		auto command = get_command(desc.begin_name);
		if (command.has_value()) {
			commands->set_begin_command(command.value());
		}
		else {
			DEBUG_ERROR_LOG("Not Add begin_DrawCommand");
		}
	}
	
	//	メイン描画コマンド設定
	if (!desc.apply_names.empty()) {

		for (auto& name : desc.apply_names) {
			auto command = get_command(name);
			if (command.has_value()) {
				commands->add_apply_command(command.value());
			}
			else {
				DEBUG_ERROR_LOG("Not Add apply_DrawCommand");
			}
		}
	}

	//	Endコマンド設定
	if (!desc.end_name.empty()) {
		auto command = get_command(desc.end_name);
		if (command.has_value()) {
			commands->set_end_command(command.value());
		}
		else {
			DEBUG_ERROR_LOG("Not Add end_DrawCommand");
		}
	}

	//  mapに登録
	auto new_hash = allocate_hash(key_name);
	draw_commands_map.emplace(new_hash, std::move(commands));

	return true;
}

//@brief	=== 描画パスコマンド取得関数 ===
//@param	key	描画パスコマンド紐づけたキー
//@return	描画パスコマンド参照
[[nodiscard]] render::dx12::command::DrawCommands* StaticDrawCommandsContainer::get_draw_commands(UINT key)const noexcept {

	const auto it = draw_commands_map.find(key);
	if (it == draw_commands_map.end()) {
		return nullptr;
	}
	return it->second.get();
}

//@breif	=== 描画パスコマンド取得関数 ===
//@param	key_name	紐づけたキーの名前
//@return	描画パスコマンドクラス参照
[[nodiscard]] render::dx12::command::DrawCommands* StaticDrawCommandsContainer::get_draw_commands(const std::string& key_name)const noexcept {

	//  キーを取得
	auto hash = get_hash_key(key_name);
	if (!hash.has_value()) {
		return nullptr;
	}

	//  上の関数に処理を任せる
	return get_draw_commands(hash.value());

}

//@brief	=== 単体コマンド取得関数 ===
//@param	key_name	取得するコマンド名
//@return	取得したコマンド...ないなら [ std::nullopt ]
[[nodiscard]] std::optional<render::dx12::utility::DrawCommand> StaticDrawCommandsContainer::get_command(std::string& key_name) {

	//	単体コマンド保存マップ探索
	auto it = command_list.find(key_name);
	if (it == command_list.end()) {
		return std::nullopt;
	}
	return it->second;
}