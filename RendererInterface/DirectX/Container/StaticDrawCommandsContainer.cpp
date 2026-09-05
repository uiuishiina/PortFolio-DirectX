#include "StaticDrawCommandsContainer.h"
#include"../../../Debug/DebugLogSystem.h"

using namespace render::dx12::container;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 追加関数 -- */

//// <summary>
/// 単体コマンド追加関数
/// </summary>
/// <param name="key">追加するコマンド名</param>
/// <param name="func">追加するコマンド</param>
/// <returns>追加の成否</returns>
[[nodiscard]] bool StaticDrawCommandsContainer::add_command_map(const handle::CommandKey& key, utility::DrawCommand&& func) {

	//	登録済みか確認
	return command_map.add_value(key, std::move(func));
}

/// <summary>
/// 描画パスコマンド作成関数
/// </summary>
/// <param name="key">登録するキーの名前</param>
/// <param name="desc">描画パスコマンド作成構造体</param>
/// <returns>作成の成否</returns>
[[nodiscard]] bool StaticDrawCommandsContainer::create_draw_commands(const handle::DrawCommandsKey& key, desc::DrawCommandDesc& desc) {

	
	//	インスタンス生成
	auto commands = std::make_unique<command::DrawCommands>();

	//	Beginコマンド設定
	if (!desc.begin_name.empty()) {
		auto command = get_command(handle::CommandKey(desc.begin_name.c_str()));
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
			auto command = get_command(handle::CommandKey(name.c_str()));
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
		auto command = get_command(handle::CommandKey(desc.end_name.c_str()));
		if (command.has_value()) {
			commands->set_end_command(command.value());
		}
		else {
			DEBUG_ERROR_LOG("Not Add end_DrawCommand");
		}
	}

	//  mapに登録
	return add_value(key, std::move(commands));
}


/* ==================================================================== */
// Privateメンバー関数
/* ==================================================================== */

/// <summary>
/// 単体コマンド取得関数
/// </summary>
/// <param name="key">取得するコマンド名</param>
/// <returns>取得したコマンド...ないなら [ std::nullopt ]</returns>
[[nodiscard]] std::optional<render::dx12::utility::DrawCommand> StaticDrawCommandsContainer::get_command(const handle::CommandKey& key) {

	//	単体コマンド保存マップ探索
	return command_map.get_value(key);
}