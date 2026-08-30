#pragma once
#include"InputEnum.h"
#include"InputState.h"
#include<tuple>

///====================================================================
/// 入力名前空間
///====================================================================

namespace input {

	///====================================================================
	/// 入力設定空間
	///====================================================================

	namespace desc {

		//@brief	=== Input用Tuple設定 ===
		using InputStates = std::tuple<
			InputState<InputKeyBoard>,
			InputState<InputMouse>
		>;
	};

	///====================================================================
	/// InputFrame 構造体
	///====================================================================

	//@breif	=== フレームキー入力まとめ構造体 ===
	struct InputFrame {

		//@brief	== tuple保存変数 ==
		desc::InputStates states_{};

		//@brief	=== メンバー変数設定用取得関数 ===
		template<HandyItems::Enum::concepts::EnumHasCount T>
		InputState<T>& set_state()noexcept {
			return std::get<InputState<T>>(states_);
		};

		//@brief	=== メンバー変数取得関数 ===
		template<HandyItems::Enum::concepts::EnumHasCount T>
		const InputState<T>& get_state()const noexcept {
			return std::get<InputState<T>>(states_);
		};
	};
};