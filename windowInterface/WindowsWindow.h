#pragma once
#include"windowInterface.h"

/* ========== 前方宣言 ========== */

/// <summary>
/// HINSTANCE用前方宣言
/// </summary>
struct HINSTANCE__;
using HINSTANCE = HINSTANCE__*;

/// <summary>
/// HWND用前方宣言
/// </summary>
struct HWND__;
using HWND = HWND__*;

/// <summary>
/// ウィンドウ名前空間
/// </summary>
namespace window {

	/// <summary>
	/// Windowsウィンドウ派生クラス
	/// </summary>
	class WindowsWindow : public windowInterface
	{
	public:
		/* ========== クラス設定 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		WindowsWindow() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~WindowsWindow() = default;


		/* ========== Publicメンバー関数 ========== */

		/* -- 継承関数 -- */

		/// <summary>
		/// ウィンドウ作成関数
		/// </summary>
		/// <param name="size">設定するウィンドウサイズ構造体</param>
		/// <returns>作成の成否</returns>
		[[nodiscard]] bool create_window(WindowSize size) override;

		/// <summary>
		/// OSイベント取得関数
		/// </summary>
		void poll_events() override;

		/// <summary>
		/// ウィンドウ終了処理関数
		/// </summary>
		void close_window() override;

		/// <summary>
		/// ウィンドウ破棄時処理関数
		/// </summary>
		void on_destroy_window() override;

		/// <summary>
		/// ウィンドウハンドル取得関数
		/// </summary>
		/// <returns>ウィンドウハンドル</returns>
		[[nodiscard]] const std::any* get_native_handle() const override;

		/// <summary>
		/// ウィンドウサイズ設定関数
		/// </summary>
		/// <param name="new_size">設定するウィンドウサイズ構造体</param>
		void set_window_size(WindowSize new_size) override;


		/* -- 独自関数 -- */

		/// <summary>
		/// ウィンドウプロシージャ互換関数
		/// </summary>
		/// <param name="msg">ウィンドウメッセージ互換</param>
		/// <param name="wParam">wParam互換</param>
		/// <param name="lParam">lParam互換</param>
		void process_message(unsigned int msg, uintptr_t wParam, intptr_t lParam);

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// ウィンドウインスタンス保存変数
		/// </summary>
		HINSTANCE hinstance_{};

		/// <summary>
		/// ウィンドウハンドル保存変数
		/// </summary>
		HWND hwnd_{};

		/* ========== Privateメンバー関数 ========== */

		/// <summary>
		/// ウィンドウリサイズ時関数
		/// </summary>
		/// <param name="new_size">設定するウィンドウサイズ構造体</param>
		void on_resize_window(WindowSize new_size);

	};
}