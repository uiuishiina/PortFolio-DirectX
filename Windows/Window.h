#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include<cstdint>
#include<utility>

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

namespace App {

	/// <summary>
	/// アプリケーションデータシェアクラス用前方宣言
	/// </summary>
	class ApplicationDataShare;
}

/// <summary>
/// Windows名前空間
/// </summary>
namespace Windows {

	/// <summary>
	/// ウィンドウサイズ構造体
	/// </summary>
	struct WindowSize {

		/* ========== メンバー変数 ========== */

		/// <summary>
		/// 横幅
		/// </summary>
		std::uint32_t width_{};

		/// <summary>
		/// 縦幅
		/// </summary>
		std::uint32_t height_{};

		/* ========== メンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		WindowSize() = default;

		/// <summary>
		/// 幅指定コンストラクタ
		/// </summary>
		/// <param name="w">横幅</param>
		/// <param name="h">縦幅</param>
		WindowSize(
			std::uint32_t w,
			std::uint32_t h
		) :
			width_{ w },
			height_{ h } {}

		/// <summary>
		/// 関数呼び出し演算子オーバーロード
		/// </summary>
		/// <returns>[ 横幅 ][ 縦幅 ] の構造化束縛</returns>
		[[nodiscard]] std::pair<
			std::uint32_t, 
			std::uint32_t
		> operator () () const {
			return { width_, height_ };
		}
	};


	/// <summary>
	/// ウィンドウクラス
	/// </summary>
	class Window final : public HandyItems::others::NonCopyableMovableBase
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		Window() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Window() = default;

		/* ===== 初期化関数 ===== */

		/// <summary>
		/// ウィンドウ初期化関数
		/// </summary>
		/// <param name="size">ウィンドウサイズ構造体</param>
		/// <param name="share">アプリケーションデータシェアクラス参照</param>
		/// <returns>初期化の成否</returns>
		[[nodiscard]] bool initialize_window(
			const WindowSize& size,
			App::ApplicationDataShare* share
		);

		/* ===== 実行関数 ===== */

		/// <summary>
		/// イベント取得関数
		/// </summary>
		void pull_event();

		/// <summary>
		/// ウィンドウ破棄命令関数
		/// </summary>
		void close_window();

		/// <summary>
		/// ウィンドウイベント振り分け関数
		/// </summary>
		/// <param name="msg">イベント識別変数</param>
		/// <param name="wParam">イベント詳細</param>
		/// <param name="lParam">イベント詳細</param>
		void process_message(
			unsigned int msg,
			uintptr_t wParam,
			intptr_t lParam
		);

		/* ===== 終了関数 ===== */

		/// <summary>
		/// ウィンドウ破棄完了関数
		/// </summary>
		void destroy_window();

		/* ===== 取得関数 ===== */

		/// <summary>
		/// ウィンドウハンドル取得関数
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] HWND get_hwnd() const noexcept {
			return hwnd_;
		}

		/// <summary>
		/// ウィンドウサイズ取得関数
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] WindowSize get_size() const noexcept {
			return size_;
		}

		/// <summary>
		/// ウィンドウフォーカスフラグ取得関数
		/// </summary>
		/// <returns>ウィンドウフォーカスフラグ</returns>
		[[nodiscard]] bool get_focus() const noexcept {
			return is_focus;
		}

		/// <summary>
		/// ウィンドウ破棄フラグ取得関数
		/// </summary>
		/// <returns>ウィンドウ破棄フラグ</returns>
		[[nodiscard]] bool get_closed() const noexcept {
			return is_closed;
		}

		/// <summary>
		/// ウィンドウ破棄完了フラグ取得関数
		/// </summary>
		/// <returns>ウィンドウ破棄完了フラグ</returns>
		[[nodiscard]] bool completed_destroy() const noexcept {
			return complete_destroy;
		}

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// ウィンドウサイズ
		/// </summary>
		WindowSize size_{};

		/// <summary>
		/// ウィンドウインスタンス
		/// </summary>
		HINSTANCE hInstance_{};

		/// <summary>
		/// ウィンドウハンドル
		/// </summary>
		HWND hwnd_{};

		/// <summary>
		/// アプリケーションデータシェアクラス参照
		/// </summary>
		App::ApplicationDataShare* shera_p{};

		/// <summary>
		/// ウィンドウフォーカスフラグ
		/// </summary>
		bool is_focus = true;

		/// <summary>
		/// ウィンドウ破棄フラグ
		/// </summary>
		bool is_closed = false;

		/// <summary>
		/// ウィンドウ破棄完了フラグ
		/// </summary>
		bool complete_destroy = false;

		/* ========== Privateメンバー関数 ========== */

	};
}