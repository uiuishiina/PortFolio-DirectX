
/* ========== Includeファイル ========== */

#include"ConvertString.h"

#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

using namespace HandyItems::Debug;

/* ========== Publicメンバー関数 ========== */

/* ===== 実行関数 ===== */

/// <summary>
/// wstring変換関数
/// </summary>
/// <param name="value">変換対象</param>
/// <returns>変換後のstring</returns>
[[nodiscard]] std::string ConvertString::to_utf8(
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
[[nodiscard]]  std::wstring ConvertString::from_utf8(
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