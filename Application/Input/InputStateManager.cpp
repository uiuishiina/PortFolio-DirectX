#include "InputStateManager.h"

using namespace input;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== フレーム更新関数 ===
//@details	キー状態を更新してリセットする関数
void InputStateManager::update_frame() {

	//	キー状態更新
	previous_state = current_state;
	current_state = {};
}

//@brief	=== 現在フレームキー設定関数 ===
void InputStateManager::set_input_frame(const InputFrame& value) {
	current_state = value;
}