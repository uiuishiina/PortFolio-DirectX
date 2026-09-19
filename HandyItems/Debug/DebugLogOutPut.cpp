
/* ========== Includeファイル ========== */

#include"DebugLogOutPut.h"
#include"HRESULTToString.h"
#include<iostream>

using namespace HandyItems::Debug;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// 出力文字列受付関数
/// </summary>
/// <param name="log">LogObject構造体</param>
void DebugLogOutPut::reception_log(
	const LogObject& log
) {

	//末尾改行を追加して出力
	OutPutLog(log.Log_data + "\n");
}

/* ========== Privateメンバー関数 ========== */

/* ===== 実行関数 ===== */

/// <summary>
/// 出力本体関数
/// </summary>
/// <param name="log">Log用文字列</param>
void DebugLogOutPut::OutPutLog(
	const std::string& log
) {

	const auto c = from_utf8(log);

    //  デバッグ出力
	OutputDebugStringW(c.c_str());

    // コンソール出力
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (console != INVALID_HANDLE_VALUE && console != nullptr) {
        DWORD written = 0;

        WriteConsoleW(
            console,
            c.data(),
            static_cast<DWORD>(c.size()),
            &written,
            nullptr
        );
    }
}