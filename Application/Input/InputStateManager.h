#pragma once
#include"InputFrame.h"
#include"Others/NonCopyableBase.h"

/// <summary>
/// 入力名前空間
/// </summary>
namespace input {

	/// <summary>
	/// 入力機能マネージャークラス
	/// </summary>
	class InputStateManager final : public others::NonCopyableBase
	{
	public:
		/* ========== クラス設定 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		InputStateManager() = default;
		
		/// <summary>
		/// デストラクタ
		/// </summary>
		~InputStateManager() = default;

		
		/* ========== Publicメンバー関数 ========== */

		/* === 更新処理関数 === */

		/// <summary>
		/// フレーム更新関数
		/// </summary>
		/// <details>
		/// キー状態を更新してリセットする関数
		/// </details>
		void update_frame() {

			//	キー状態更新
			previous_state = current_state;
			current_state = {};
		}


		/* === 状態セット関数 === */

		/// <summary>
		/// 現在フレームキー参照取得関数
		/// </summary>
		/// <returns>現在フレームキー参照</returns>
		[[nodiscard]] InputFrame& get_current_state() noexcept {
			return current_state;
		}


		/* === キーフラグ取得関数 === */

		/// <summary>
		/// 入力中取得関数
		/// </summary>
		/// <typeparam name="T">取得したい列挙体</typeparam>
		/// <param name="value">取得したいキー</param>
		/// <returns>入力されているなら [ true ]</returns>
		template<HandyItems::Enum::concepts::EnumHasCount T>
		[[nodiscard]] bool is_pressed(T value) const noexcept {
			return get_current_key(value);
		};

		/// <summary>
		/// 入力開始取得関数
		/// </summary>
		/// <typeparam name="T">取得したい列挙体</typeparam>
		/// <param name="value">取得したいキー</param>
		/// <returns>入力されているなら [ true ]</returns>
		template<HandyItems::Enum::concepts::EnumHasCount T>
		[[nodiscard]] bool is_down(T value) const noexcept {
			return	get_current_key(value) && !get_previous_key(value);
		};

		/// <summary>
		/// 入力終了取得関数
		/// </summary>
		/// <typeparam name="T">取得したい列挙体</typeparam>
		/// <param name="value">取得したいキー</param>
		/// <returns>入力されているなら [ true ]</returns>
		template<HandyItems::Enum::concepts::EnumHasCount T>
		[[nodiscard]] bool is_up(T value) const noexcept {
			return	!get_current_key(value) && get_previous_key(value);
		};

	private:
		/* ========== Privateメンバー変数 ========== */
		
		/// <summary>
		/// 現在フレームキー状態保存変数
		/// </summary>
		InputFrame current_state{};

		/// <summary>
		/// 前フレームキー状態保存変数
		/// </summary>
		InputFrame previous_state{};


		/* ========== Privateメンバー関数 ========== */

		/* === キー取得関数 === */

		/// <summary>
		/// 現在フレームキー状態取得関数
		/// </summary>
		/// <typeparam name="T">取得したい列挙体</typeparam>
		/// <param name="value">取得したいキー</param>
		/// <returns>入力されているなら [ true ]</returns>
		template<HandyItems::Enum::concepts::EnumHasCount T>
		[[nodiscard]] bool get_current_key(T value) const noexcept {
			return current_state.get_input_state<T>().get_key(value);
		};

		/// <summary>
		/// 前フレームキー状態取得関数
		/// </summary>
		/// <typeparam name="T">取得したい列挙体</typeparam>
		/// <param name="value">取得したいキー</param>
		/// <returns>入力されていたなら [ true ]</returns>
		template<HandyItems::Enum::concepts::EnumHasCount T>
		[[nodiscard]] bool get_previous_key(T value) const noexcept {
			return previous_state.get_input_state<T>().get_key(value);
		};

	};
}