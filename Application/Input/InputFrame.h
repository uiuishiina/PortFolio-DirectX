#pragma once
#include"InputEnum.h"
#include"InputState.h"
#include"Others/NonCopyableBase.h"
#include"Tuple/TupleBase.h"

/// <summary>
/// 入力名前空間
/// </summary>
namespace input {
	
	/// <summary>
	/// フレーム別キー入力状態構造体
	/// </summary>
	class InputFrame
	{
	public:
		/* ========== クラス設定 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		InputFrame() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~InputFrame() = default;


		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// フレーム別入力キー状態構造体参照取得関数
		/// </summary>
		/// <typeparam name="T">取得したいキー列挙体</typeparam>
		/// <returns>取得した参照</returns>
		template<HandyItems::Enum::concepts::EnumHasCount T>
		[[nodiscard]] InputState<T>& get_input_state() {
			return input_tuple.get_value<InputState<T>>();
		}

		template<HandyItems::Enum::concepts::EnumHasCount T>
		[[nodiscard]] const InputState<T>& get_input_state() const {
			return input_tuple.get_value<InputState<T>>();
		}

	private:
		/* ========== メンバー変数 ========== */

		/// <summary>
		/// 入力状態構造体まとめ
		/// </summary>
		HandyItems::tuple::TupleBase<
			InputState<InputKeyBoard>,
			InputState<InputMouse>
		> input_tuple{};
	};
}