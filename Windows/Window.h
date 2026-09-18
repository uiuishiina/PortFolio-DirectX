#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include<cstdint>
#include<memory>

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

		/* ===== 演算子オーバーロード ===== */

		/// <summary>
		/// [ () ] 演算子オーバーロード
		/// </summary>
		/// <returns>[ 横幅 ][ 縦幅 ] の構造化束縛</returns>
		[[nodiscard]] auto operator () () const {
			return std::make_pair(width_, height_);
		}
	};


	/// <summary>
	/// ウィンドウクラス
	/// </summary>
	class Window final : public HandyItems::others::NonCopyableBase
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		Window();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Window();

		/* ===== 初期化関数 ===== */

		[[nodiscard]] bool initialize_window(
			const WindowSize& size,
			App::ApplicationDataShare* share
		);

		/* ===== 実行関数 ===== */

		void pull_event();

		void close_window();

		void destroy_window();

		void process_message(
			unsigned int msg,
			uintptr_t wParam,
			intptr_t lParam
		);

		/* ===== 取得関数 ===== */

		[[nodiscard]] HWND get_hwnd() const noexcept {
			return hwnd_;
		}

		[[nodiscard]] bool get_focus() const noexcept {
			return is_focus;
		}

		[[nodiscard]] bool get_closed() const noexcept {
			return is_closed;
		}

		[[nodiscard]] bool completed_destroy() const noexcept {
			return complete_destroy;
		}

	private:
		/* ========== Privateメンバー変数 ========== */

		WindowSize size_{};

		HINSTANCE hInstance_{};

		HWND hwnd_{};

		App::ApplicationDataShare* shera_p{};

		bool is_focus = true;

		bool is_closed = false;

		bool complete_destroy = false;

		/* ========== Privateメンバー関数 ========== */


	};
}