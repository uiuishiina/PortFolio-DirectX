
/* ========== Includeファイル ========== */

#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

#include"Window.h"
#include"../Application/ApplicationDataShare.h"
#include"./Debug/DebugLogSystem.h"

using namespace Windows;
using namespace HandyItems;

/* ========== 無名空間 ========== */

namespace {

    unsigned long style_ = WS_OVERLAPPEDWINDOW;

    const wchar_t* class_name = L"main_window";
    const wchar_t* window_name = L"MainWindow";

    /// <summary>
   /// ウィンドウプロシージャ関数
   /// </summary>
   /// <param name="hwnd">ウィンドウハンドル</param>
   /// <param name="msg">ウィンドウメッセージ</param>
   /// <param name="wParam">wParam</param>
   /// <param name="lParam">lParam</param>
    static LRESULT CALLBACK static_window_proc(
        HWND hwnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
    ) {

        /* ===== 初期化時 ===== */
        if (msg == WM_NCCREATE) {
            
            auto cs = reinterpret_cast<CREATESTRUCT*>(lParam);
            auto pWnd = reinterpret_cast<Window*>(cs->lpCreateParams);

            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

            return true;
        }

        /* ===== 実行時 ===== */
        if (auto pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)); pWnd) {
            switch (msg)
            {
            //  破棄呼び出し時
            case WM_CLOSE: {

                pWnd->close_window();
                return {};
            }
            //  最終破棄時
            case WM_NCDESTROY: {

                SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
                pWnd->destroy_window();
                break;
            }
            //  クラス関数
            default:
                pWnd->process_message(msg, wParam, lParam);
            }
        }
        
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    /// <summary>
    /// ウィンドウサイズ補正補助関数
    /// </summary>
    /// <details>
    /// ウィンドウバーがある場合にバーのサイズを除き、描画できる範囲を出してくれる
    /// </details>
    /// <param name="new_size">補正するウィンドウサイズ構造体</param>
    /// <param name="style">補正するウィンドウスタイル設定</param>
    /// <returns>補正したウィンドウサイズ構造体</returns>
    static WindowSize adjust_window_size(
        WindowSize new_size,
        unsigned long style
    ) {

        RECT rc{ 
            0, 
            0, 
            static_cast<long>(new_size.width_), 
            static_cast<long>(new_size.height_) 
        };
        AdjustWindowRect(&rc, style, FALSE);

        return WindowSize(
            rc.right - rc.left, 
            rc.bottom - rc.top
        );
    }
}

/* ========== Publicメンバー関数 ========== */

/* ===== 初期化関数 ===== */

/// <summary>
/// ウィンドウ初期化関数
/// </summary>
/// <param name="size">ウィンドウサイズ構造体</param>
/// <param name="share">アプリケーションデータシェアクラス参照</param>
/// <returns>初期化の成否</returns>
[[nodiscard]] bool Window::initialize_window(
    const WindowSize& size,
    App::ApplicationDataShare* share
) {

    //  すでにインスタンスがあるなら作成せず失敗を返す
    if (hInstance_) {
        return false;
    }

    size_ = size;

    shera_p = share;

    //  ウィンドウインスタンスを [ WindowsOS ] から取得
    hInstance_ = GetModuleHandle(nullptr);

    //  補助関数経由で画面サイズ取得
    auto adjust = adjust_window_size(size, style_);

    //  ウィンドウクラス登録
    WNDCLASS wc{};
    wc.lpfnWndProc = static_window_proc;
    wc.lpszClassName = class_name;
    wc.hInstance = hInstance_;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    //  登録失敗なら失敗を返す
    //  二重登録でもfalseだが今回は失敗とする
    if (!RegisterClass(&wc)) {
        return false;
    }

    //  ウィンドウ作成
    hwnd_ = CreateWindow(
        wc.lpszClassName,
        window_name,
        style_,
        CW_USEDEFAULT, CW_USEDEFAULT,
        adjust.width_,
        adjust.height_,
        nullptr, nullptr, 
        hInstance_, 
        this
    );

    //  ウィンドウが作成できたか
    if (!hwnd_) {
        return false;
    }

    //  ウィンドウ表示
    ShowWindow(hwnd_, SW_SHOW);

    //  ウィンドウ開始
    UpdateWindow(hwnd_);

    //  ウィンドウフォーカス
    SetForegroundWindow(hwnd_);
    SetFocus(hwnd_);

    return true;
}

/* ===== 実行関数 ===== */

/// <summary>
/// イベント取得関数
/// </summary>
void Window::pull_event() {

    //  メッセージループ処理開始
    MSG msg{};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

        if (msg.message == WM_QUIT) {
            //PostQuitMessage()されたならここに
            return;
        }

        //  static_window_procに送る
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

/// <summary>
/// ウィンドウ破棄命令関数
/// </summary>
void Window::close_window() {

    if (is_closed) { return; }
    is_closed = true;
    DestroyWindow(hwnd_);
}

/// <summary>
/// ウィンドウイベント振り分け関数
/// </summary>
/// <param name="msg">イベント識別変数</param>
/// <param name="wParam">イベント詳細</param>
/// <param name="lParam">イベント詳細</param>
void Window::process_message(
    unsigned int msg,
    uintptr_t wParam,
    intptr_t lParam
) {

    switch (msg)
    {

        /* ========== キー入力取得 ========== */

    case WM_KEYDOWN: {  // 押されたとき
        bool repeat = (lParam & (1 << 30)) != 0;
        if (repeat) {
            break;
        }
        auto& keyboard = shera_p->get_input()->get_current_state().get_input_state<input::InputKeyBoard>();

        switch (wParam)
        {
        case VK_ESCAPE:
            keyboard.set_key(input::InputKeyBoard::Esc, true);
            break;
        case VK_LEFT:
            keyboard.set_key(input::InputKeyBoard::LeftArrow, true);
            break;
        case VK_RIGHT:
            keyboard.set_key(input::InputKeyBoard::RightArrow, true);
            break;
        case '1':
            keyboard.set_key(input::InputKeyBoard::One, true);
            break;
        }
        break;
    }
    case WM_KEYUP: {    // 離されたとき

        auto& keyboard = shera_p->get_input()->get_current_state().get_input_state<input::InputKeyBoard>();

        switch (wParam)
        {
        case VK_ESCAPE:
            keyboard.set_key(input::InputKeyBoard::Esc, false);
            break;
        case VK_LEFT:
            keyboard.set_key(input::InputKeyBoard::LeftArrow, false);
            break;
        case VK_RIGHT:
            keyboard.set_key(input::InputKeyBoard::RightArrow, false);
            break;
        case '1':
            keyboard.set_key(input::InputKeyBoard::One, false);
            break;
        }
        break;
    }
        /* ========== ウィンドウフォーカス取得 ========== */
    case WM_SETFOCUS: {
        is_focus = true;
        break;
    }
    case WM_KILLFOCUS: {
        is_focus = false;
        break;
    }
    default:
        break;
    }
}

/* ===== 終了関数 ===== */

/// <summary>
/// ウィンドウ破棄完了関数
/// </summary>
void Window::destroy_window() {

    complete_destroy = true;
    PostQuitMessage(0);
}
