#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

#include"WindowsWindow.h"

///====================================================================
/// 無名空間
///====================================================================

namespace {
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

    ///====================================================================
    /// 補助関数
    ///====================================================================

    //@brief    === ウィンドウサイズ取得補助関数 ===
    //@details  ウィンドウバーがある場合にバーのサイズを除き、描画できる範囲を出してくれる
    //@details  WS_OVERLAPPEDWINDOW　を変えればその他のウィンドウもできるため改良の余地あり
    static WindowSize adjust_window_size(WindowSize new_size) {

        RECT rc{ 0, 0, new_size.width,new_size.height };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        return WindowSize(rc.right - rc.left, rc.bottom - rc.top);
    }
}

///====================================================================
/// 初期化時関数
///====================================================================

//@breif	=== ウィンドウ作成関数 ===
//@param	window_size	ウィンドウサイズ
//@return	作成の可否
[[nodiscard]] bool WindowsWindow::create_window(WindowSize size) {

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

    return true;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== ウィンドウプロシージャ互換関数 ===
//@param	msg	ウィンドウメッセージ互換
//@param	wParam	wParam互換
//@param	lParam	lParam互換
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
            current_frame_key.set_state<input::InputKeyBoard>().set_key(input::InputKeyBoard::Esc, true);
            break;
        case VK_LEFT:
            current_frame_key.set_state<input::InputKeyBoard>().set_key(input::InputKeyBoard::LeftArrow, true);
            break;
        case VK_RIGHT:
            current_frame_key.set_state<input::InputKeyBoard>().set_key(input::InputKeyBoard::RightArrow, true);
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

//@brief	=== ウィンドウ終了処理関数 ===
void WindowsWindow::close_window() {

    //  ウィンドウ終了フラグオン
    should_close = true;

    //  ウィンドウ破棄通知をOSに送る
    DestroyWindow(hwnd_);
}

//@breif	=== ウィンドウ破棄時処理関数 ===
void WindowsWindow::on_destroy_window() {

    //  ウィンドウ情報破棄
    hwnd_ = nullptr;
    hinstance_ = nullptr;

    //  ウィンドウ破棄フラグオン
    complete_destroy = true;

    //  ウィンドウで使っていたメッセージループ終了
    PostQuitMessage(0);
}

//@brief	=== OSイベント取得関数 ===
void WindowsWindow::poll_events() {

    // キー入力変数初期化
    current_frame_key = {};

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

//@brief	=== ウィンドウサイズ設定関数 ===
//@param	new_size	ウィンドウサイズ
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

//@brief	=== ウィンドウリサイズ時関数 ===
//@param	new_size	ウィンドウサイズ
void WindowsWindow::on_resize_window(WindowSize new_size) {
    window_size = new_size;
}

///====================================================================
/// 取得関数
///====================================================================

//@brief	=== ウィンドウハンドル取得関数 ===
//@return	ウィンドウハンドルポインター
void* WindowsWindow::get_native_handle()const {
    return hwnd_;
}