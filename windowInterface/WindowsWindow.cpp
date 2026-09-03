#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

#include"WindowsWindow.h"

using namespace window;

/* ==================================================================== */
// 無名空間
/* ==================================================================== */

namespace {

    /// <summary>
    /// ウィンドウプロシージャ関数
    /// </summary>
    /// <param name="hwnd">ウィンドウハンドル</param>
    /// <param name="msg">ウィンドウメッセージ</param>
    /// <param name="wParam">wParam</param>
    /// <param name="lParam">lParam</param>
    static LRESULT CALLBACK static_window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg)
        {
        case WM_NCCREATE: { //初期化
            auto cs = reinterpret_cast<CREATESTRUCT*>(lParam);
            auto pWnd = reinterpret_cast<WindowsWindow*>(cs->lpCreateParams);

            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
            break;
        }
        case WM_CLOSE: {    //破棄時
            auto pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (pWnd) {
                pWnd->close_window();
            }
            return 0;
        }
        case WM_NCDESTROY: {    //最終破棄
            auto pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (pWnd) {
                SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
                pWnd->on_destroy_window();
            }
            return 0;
        }
        default:
            break;
        }
        auto pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if (pWnd) {
            pWnd->process_message(msg, wParam, lParam);
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    /* ==================================================================== */
    // 補助関数
    /* ==================================================================== */

    /// <summary>
    /// ウィンドウサイズ補正補助関数
    /// </summary>
    /// <details>
    /// ウィンドウバーがある場合にバーのサイズを除き、描画できる範囲を出してくれる
    /// [ WS_OVERLAPPEDWINDOW ] を変えればその他のウィンドウもできるため改良の余地あり
    /// </details>
    /// <param name="new_size">補正するウィンドウサイズ構造体</param>
    /// <returns>補正したウィンドウサイズ構造体</returns>
    static WindowSize adjust_window_size(WindowSize new_size) {

        RECT rc{ 0, 0, new_size.width,new_size.height };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        return WindowSize(rc.right - rc.left, rc.bottom - rc.top);
    }
}

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// ウィンドウ作成関数
/// </summary>
/// <param name="size">設定するウィンドウサイズ構造体</param>
/// <returns>作成の成否</returns>
[[nodiscard]] bool WindowsWindow::create_window(WindowSize size, input::InputStateManager* input_) {

    //  すでにインスタンスがあるなら作成せず失敗を返す
    if (hinstance_) {
        return false;
    }

    //  ウィンドウインスタンスを [ WIndowsOS ] から取得
    hinstance_ = GetModuleHandle(nullptr);

    //  補助関数経由で画面サイズ取得
    auto adjust = adjust_window_size(size);

    //  ウィンドウクラス登録
    WNDCLASS wc{};
    wc.lpfnWndProc = static_window_proc;
    wc.lpszClassName = L"windows_window";
    wc.hInstance = hinstance_;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    //  登録失敗なら失敗を返す
    //  二重登録でもfalseだが今回は失敗とする
    if (!RegisterClass(&wc)) {
        return false;
    }
    
    //  ウィンドウ作成
    hwnd_ = CreateWindow(
        wc.lpszClassName, wc.lpszClassName,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
        adjust.width, adjust.height,
        nullptr, nullptr, hinstance_, this);

    //  ウィンドウが作成できたか
    if (!hwnd_) {
        return false;
    }

    //  ウィンドウ表示
    ShowWindow(hwnd_, SW_SHOW);

    //  ウィンドウ開始
    UpdateWindow(hwnd_);

    //  ウィンドウサイズ保存
    window_size = size;

    native_handle = hwnd_;

    input_manager = input_;

    return true;
}

/// <summary>
/// OSイベント取得関数
/// </summary>
void WindowsWindow::poll_events() {

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
/// ウィンドウ終了処理関数
/// </summary>
void WindowsWindow::close_window() {

    //  ウィンドウ終了フラグオン
    should_close = true;

    //  ウィンドウ破棄通知をOSに送る
    DestroyWindow(hwnd_);
}

/// <summary>
/// ウィンドウ破棄時処理関数
/// </summary>
void WindowsWindow::on_destroy_window() {

    //  ウィンドウ情報破棄
    hwnd_ = nullptr;
    hinstance_ = nullptr;
    native_handle = nullptr;

    //  ウィンドウ破棄フラグオン
    complete_destroy = true;

    //  ウィンドウで使っていたメッセージループ終了
    PostQuitMessage(0);
}

/// <summary>
/// ウィンドウハンドル取得関数
/// </summary>
/// <returns>ウィンドウハンドル</returns>
[[nodiscard]] const std::any* WindowsWindow::get_native_handle()const {
    return &native_handle;
}

/// <summary>
/// ウィンドウサイズ設定関数
/// </summary>
/// <param name="new_size">設定するウィンドウサイズ構造体</param>
void WindowsWindow::set_window_size(WindowSize new_size) {

    auto size = adjust_window_size(new_size);

    SetWindowPos(
        hwnd_, nullptr,
        0, 0,
        size.width,
        size.height,
        SWP_NOMOVE | SWP_NOZORDER
    );
}

/// <summary>
/// ウィンドウプロシージャ互換関数
/// </summary>
/// <param name="msg">ウィンドウメッセージ互換</param>
/// <param name="wParam">wParam互換</param>
/// <param name="lParam">lParam互換</param>
void WindowsWindow::process_message(unsigned int msg, uintptr_t wParam, intptr_t lParam) {
    switch (msg)
    {
    case WM_KEYDOWN: {  //キー入力取得
        bool repeat = (lParam & (1 << 30)) != 0;
        if (repeat) {
            break;
        }
        switch (wParam)
        {
        case VK_ESCAPE:
            input_manager->get_current_state().get_input_state<input::InputKeyBoard>().set_key(input::InputKeyBoard::Esc, true);
            break;
        case VK_LEFT:
            input_manager->get_current_state().get_input_state<input::InputKeyBoard>().set_key(input::InputKeyBoard::LeftArrow, true);
            break;
        case VK_RIGHT:
            input_manager->get_current_state().get_input_state<input::InputKeyBoard>().set_key(input::InputKeyBoard::RightArrow, true);
            break;
        }
        break;
    }
    case WM_SETFOCUS: {
        is_active = true;
        break;
    }
    case WM_KILLFOCUS: {
        is_active = false;
        break;
    }
    case WM_SIZE: {
        //リサイズ時
        on_resize_window(WindowSize(LOWORD(lParam), HIWORD(lParam)));
        break;
    }
    default:
        break;
    }
}

/* ==================================================================== */
// Privateメンバー関数
/* ==================================================================== */

/// <summary>
/// ウィンドウリサイズ時関数
/// </summary>
/// <param name="new_size">設定するウィンドウサイズ構造体</param>
void WindowsWindow::on_resize_window(WindowSize new_size) {
    window_size = new_size;
}
