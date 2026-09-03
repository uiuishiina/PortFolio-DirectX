#pragma once
#include"WindowSize.h"
#include"../Application/Input/InputFrame.h"
#include"Others/NonCopyableBase.h"
#include<any>

/// <summary>
/// ウィンドウ名前空間
/// </summary>
namespace window {

	/// <summary>
	/// ウィンドウインターフェース基底クラス
	/// </summary>
	class windowInterface : public others::NonCopyableBase
	{
	public:
		/* ========== クラス設定 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		windowInterface() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~windowInterface() = default;


		/* ========== Publicメンバー関数 ========== */

		/* === 純粋仮想関数 === */

		/// <summary>
		/// ウィンドウ作成関数
		/// </summary>
		/// <param name="size">設定するウィンドウサイズ構造体</param>
		/// <returns>作成の成否</returns>
		[[nodiscard]] virtual bool create_window(WindowSize size) = 0;

		/// <summary>
		/// OSイベント取得関数
		/// </summary>
		virtual void poll_events() = 0;

		/// <summary>
		/// ウィンドウ終了処理関数
		/// </summary>
		virtual void close_window() = 0;

		/// <summary>
		/// ウィンドウ破棄時処理関数
		/// </summary>
		virtual void on_destroy_window() = 0;

		/// <summary>
		/// ウィンドウハンドル取得関数
		/// </summary>
		/// <returns>ウィンドウハンドル</returns>
		[[nodiscard]] virtual const std::any* get_native_handle() const = 0;

		/// <summary>
		/// ウィンドウサイズ設定関数
		/// </summary>
		/// <param name="new_size">設定するウィンドウサイズ構造体</param>
		virtual void set_window_size(WindowSize new_size) = 0;


		/* === 共通フラグ & 変数 取得関数 === */

		/// <summary>
		/// 現在フレームキー状態取得関数
		/// </summary>
		/// <returns>現在フレームキー</returns>
		[[nodiscard]] input::InputFrame get_input_frame()const noexcept {
			return current_frame_key;
		}

		/// <summary>
		/// ウィンドウサイズ取得関数
		/// </summary>
		/// <returns>ウィンドウサイズ構造体</returns>
		[[nodiscard]] WindowSize get_window_size()const noexcept {
			return window_size;
		}

		/// <summary>
		/// ウィンドウ終了フラグ取得関数
		/// </summary>
		/// <returns>ウィンドウ終了フラグ</returns>
		[[nodiscard]] bool should_close_window()const noexcept {
			return should_close;
		}

		/// <summary>
		/// ウィンドウアクティブフラグ取得関数
		/// </summary>
		/// <returns>ウィンドウアクティブフラグ</returns>
		[[nodiscard]] bool is_active_window()const noexcept {
			return is_active;
		}

		/// <summary>
		/// ウィンドウ破棄状態取得関数
		/// </summary>
		/// <returns>ウィンドウ破棄完了フラグ</returns>
		[[nodiscard]] bool is_complete_destroy_window()const noexcept {
			return complete_destroy;
		}

	protected:
		/* ========== Protectedメンバー関数 ========== */

		/// <summary>
		/// ウィンドウ終了フラグ
		/// </summary>
		/// <details>
		/// ウィンドウ終了指令が来たなら [ true ]
		/// </details>
		bool should_close = false;

		/// <summary>
		/// ウィンドウアクティブフラグ
		/// </summary>
		/// <details>
		/// ウィンドウがアクティブなら [ true ]
		/// </details>
		bool is_active = true;

		/// <summary>
		/// ウィンドウ破棄完了フラグ
		/// </summary>
		/// <details>
		/// 完全に破棄できたなら [ true ]
		/// </details>
		bool complete_destroy = false;

		/// <summary>
		/// ウィンドウハンドル保存変数
		/// </summary>
		/// <details>
		/// 外部に共有用として作成(無くなるかもね)
		/// </details>
		std::any native_handle{};

		/// <summary>
		/// ウィンドウサイズ保存変数
		/// </summary>
		WindowSize window_size{};

		/// <summary>
		/// 現在フレームキー状態保存変数
		/// </summary>
		/// <details>
		/// フレーム毎に更新
		/// </details>
		input::InputFrame current_frame_key{};

	};
}