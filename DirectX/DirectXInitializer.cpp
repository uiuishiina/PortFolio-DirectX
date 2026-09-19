
/* ========== Includeファイル ========== */

#include"DirectXInitializer.h"
#include"Debug/DebugLogSystem.h"
#include"Debug/HRESULTToString.h"

using namespace DirectX;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// HRESULTログ出力関数
/// </summary>
/// <param name="hr">ログに出力するHRESULT</param>
void InitializeLog::hresult_log(
	HRESULT hr
) {

	DEBUG_LOG(HandyItems::Debug::hresult_to_string(hr));
}

/// <summary>
/// HRESULTエラーログ出力関数
/// </summary>
/// <param name="hr">ログに出力するHRESULT</param>
void InitializeLog::hresult_error_log(
	HRESULT hr
) {

	DEBUG_ERROR_LOG(HandyItems::Debug::hresult_to_string(hr));
}