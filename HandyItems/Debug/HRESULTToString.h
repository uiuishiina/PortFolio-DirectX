#pragma once

/* ========== Includeファイル ========== */

#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

#include"ConvertString.h"

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// デバッグ名前空間
	/// </summary>
	namespace Debug {

        /// <summary>
        /// HRESULT変換関数
        /// </summary>
        /// <param name="hr">変換するHRESULT</param>
        /// <returns>変換した文字列</returns>
        [[nodiscard]] inline std::string hresult_to_string(
            HRESULT hr
        ) {

            wchar_t* message = nullptr;

            const DWORD length = FormatMessageW(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr,
                static_cast<DWORD>(hr),
                0,
                reinterpret_cast<LPWSTR>(&message),
                0,
                nullptr
            );

            std::wstring message_w;

            if (length != 0 && message) {
                message_w.assign(message, length);
            }

            if (message) {
                LocalFree(message);
            }

            while (
                !message_w.empty() && 
                (
                    message_w.back() == L'\r' ||
                    message_w.back() == L'\n'
                )
                ) {

                message_w.pop_back();
            }

            return ConvertString::to_utf8(message_w);
        }
	}
}