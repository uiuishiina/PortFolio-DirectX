#pragma once

/* ========== Includeファイル ========== */

#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<string>

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// デバッグ名前空間
	/// </summary>
	namespace Debug {

        /// <summary>
        /// wstring変換関数
        /// </summary>
        /// <param name="value">変換対象</param>
        /// <returns>変換後のstring</returns>
        [[nodiscard]] inline std::string to_utf8(
            const std::wstring& value
        ) {

            if (value.empty()) {
                return {};
            }

            const int size = WideCharToMultiByte(
                CP_UTF8,
                WC_ERR_INVALID_CHARS,
                value.data(),
                static_cast<int>(value.size()),
                nullptr,
                0,
                nullptr,
                nullptr
            );

            if (size <= 0) {
                return {};
            }

            std::string result(size, '\0');

            WideCharToMultiByte(
                CP_UTF8,
                0,
                value.data(),
                static_cast<int>(value.size()),
                result.data(),
                size,
                nullptr,
                nullptr
            );

            return result;
        }

        /// <summary>
        /// string変換関数
        /// </summary>
        /// <param name="value">変換対象</param>
        /// <returns>変換後のwstring</returns>
        [[nodiscard]] inline std::wstring from_utf8(
            const std::string& value
        ) {

            if (value.empty()) {
                return {};
            }

            const int size = MultiByteToWideChar(
                CP_UTF8,
                MB_ERR_INVALID_CHARS,
                value.data(),
                static_cast<int>(value.size()),
                nullptr,
                0
            );

            if (size <= 0) {
                return {};
            }

            std::wstring result(size, L'\0');

            const int converted = MultiByteToWideChar(
                CP_UTF8,
                MB_ERR_INVALID_CHARS,
                value.data(),
                static_cast<int>(value.size()),
                result.data(),
                size
            );

            if (converted <= 0) {
                return {};
            }

            result.resize(static_cast<std::size_t>(converted));

            return result;
        }

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

            return to_utf8(message_w);
        }
	}
}