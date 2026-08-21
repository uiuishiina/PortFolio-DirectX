#pragma once
#include"InputFrame.h"
#include"NonMovable.h"

///====================================================================
/// 入力名前空間
///====================================================================

namespace input {

	///====================================================================
	/// InputStateManager クラス
	///====================================================================

	//@brief	=== 
	class InputStateManager final : public NonMovableBase
	{
	public:
		///====================================================================
		/// クラス設定
		///====================================================================

		//コンストラクタ,デストラクタ
		InputStateManager() = default;
		~InputStateManager() = default;

		///====================================================================
		/// Public メンバー関数
		///====================================================================

		/* === 更新処理関数 === */

		//@brief	=== フレーム更新関数 ===
		//@details	キー状態を更新してリセットする関数
		void update_frame();


		/* === 状態セット関数 === */

		//@brief	=== 現在フレームキー設定関数 ===
		void set_input_frame(const InputFrame& value);


		/* === キーフラグ取得関数 === */

		//@brief	=== 入力中取得関数 ===
		//@param	value	取得したいキー
		//@return	入力されているかどうか
		template<concepts::Enum_has_Count T>
		[[nodiscard]] bool is_pressed(T value)const noexcept;

		//@brief	=== 入力開始取得関数 ===
		//@param	value	取得したいキー
		//@return	入力されているかどうか
		template<concepts::Enum_has_Count T>
		[[nodiscard]] bool is_down(T value)const noexcept;

		//@brief	=== 入力終了取得関数 ===
		//@param	value	取得したいキー
		//@return	入力されているかどうか
		template<concepts::Enum_has_Count T>
		[[nodiscard]] bool is_up(T value)const noexcept;

	private:
		///====================================================================
		/// Private メンバー変数
		///====================================================================

		//@breif	== 現在フレームキー状態保存変数 ==
		InputFrame current_state{};

		//@breif	== 前フレームキー状態保存変数 ==
		InputFrame previous_state{};

		///====================================================================
		/// Private メンバー関数
		///====================================================================

		/* === キー取得関数 === */

		//@brief	=== 現在フレームキー状態取得関数 ===
		//@param	value	取得したいキー
		//@return	キー状態
		template<concepts::Enum_has_Count T>
		[[nodiscard]] bool get_current_key(T value)const noexcept;

		//@brief	=== 前フレームキー状態取得関数 ===
		//@param	value	取得したいキー
		//@return	キー状態
		template<concepts::Enum_has_Count T>
		[[nodiscard]] bool get_previous_key(T value)const noexcept;

	};

	/* === キー取得関数 === */

	//@brief	=== 現在キー状態取得関数 ===
	//@param	value	取得したいキー
	//@return	キー状態
	template<concepts::Enum_has_Count T>
	[[nodiscard]] bool InputStateManager::get_current_key(T value)const noexcept {
		return current_state.get_state<T>().get_key(value);
	};

	//@brief	=== 前フレームキー状態取得関数 ===
	//@param	value	取得したいキー
	//@return	キー状態
	template<concepts::Enum_has_Count T>
	[[nodiscard]] bool InputStateManager::get_previous_key(T value)const noexcept {
		return previous_state.get_state<T>().get_key(value);
	};

	/* === キーフラグ取得関数 === */

	//@brief	=== 入力中取得関数 ===
	//@param	value	取得したいキー
	//@return	入力されているかどうか
	template<concepts::Enum_has_Count T>
	[[nodiscard]] bool InputStateManager::is_pressed(T value)const noexcept {
		return get_current_key(value);
	};

	//@brief	=== 入力開始取得関数 ===
	//@param	value	取得したいキー
	//@return	入力されているかどうか
	template<concepts::Enum_has_Count T>
	[[nodiscard]] bool InputStateManager::is_down(T value)const noexcept {
		return	get_current_key(value) && !get_previous_key(value);
	};

	//@brief	=== 入力終了取得関数 ===
	//@param	value	取得したいキー
	//@return	入力されているかどうか
	template<concepts::Enum_has_Count T>
	[[nodiscard]] bool InputStateManager::is_up(T value)const noexcept {
		return	!get_current_key(value) && get_previous_key(value);
	};
};