#pragma once
#include"InputEnum.h"
#include"InputState.h"
#include<tuple>

///====================================================================
/// 入力名前空間
///====================================================================

namespace input {

	///====================================================================
	/// InputFrame 構造体
	///====================================================================

	//@breif	=== フレームキー入力まとめ構造体 ===
	struct InputFrame {

		//@brief	=== tuple用メンバー変数作成 ===
		using States = std::tuple<
			InputState<InputKeyBoard>
		>;

		//@brief	== tuple保存変数 ==
		States states_{};

		//@brief	=== メンバー変数設定用取得関数 ===
		template<concepts::Enum_has_Count T>
		InputState<T>& set_state()noexcept {
			return std::get<InputState<T>>(states_);
		};

		//@brief	=== メンバー変数取得関数 ===
		template<concepts::Enum_has_Count T>
		const InputState<T>& get_state()const noexcept {
			return std::get<InputState<T>>(states_);
		};
	};
};