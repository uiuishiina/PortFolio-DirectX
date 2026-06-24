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
            DestroyWindow(hwnd);
            break;
        }
        case WM_NCDESTROY: {    //最終破棄
            auto pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (pWnd) {
                SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
                pWnd->on_destroy_window();
            }
            break;
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

    if (hinstance_) {
        return false;
    }

    hinstance_ = GetModuleHandle(nullptr);

    auto adjust = adjust_window_size(size);

    WNDCLASS wc{};
    wc.lpfnWndProc = static_window_proc;
    wc.lpszClassName = L"windows_window";
    wc.hInstance = hinstance_;

    if (!RegisterClass(&wc)) {
        return false;
    }
    

    hwnd_ = CreateWindow(
        wc.lpszClassName, wc.lpszClassName,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
        adjust.width, adjust.height,
        nullptr, nullptr, hinstance_, this);

    if (!hwnd_) {
        return false;
    }
    ShowWindow(hwnd_, SW_SHOW);

    UpdateWindow(hwnd_);

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
            DestroyWindow(hwnd_);
            break;
        case VK_LEFT:
            break;
        case VK_RIGHT:
            break;
        }
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

//@breif	=== ウィンドウ破棄時処理関数 ===
void WindowsWindow::on_destroy_window() {
    hwnd_ = nullptr;
    hinstance_ = nullptr;

    PostQuitMessage(0);
}

//@brief	=== OSイベント取得関数 ===
void WindowsWindow::poll_events() {
    MSG msg{};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            is_stop = true;
        }
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

//@breif	=== ウィンドウ破棄フラグ取得関数 ===
//@return	ウィンドウ破棄フラグ
bool WindowsWindow::should_close_window()const {
    return is_stop;
}

//@brief	=== ウィンドウサイズ取得関数 ===
//@return	ウィンドウサイズ構造体
WindowSize WindowsWindow::get_window_size()const {
    return window_size;
}

//@brief	=== ウィンドウハンドル取得関数 ===
//@return	ウィンドウハンドルポインター
void* WindowsWindow::get_native_handle()const {
    return hwnd_;
}