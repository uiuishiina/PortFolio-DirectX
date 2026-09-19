
/* ========== Includeファイル ========== */

#include"DebugLogThread.h"	//	DebugLogThread用
#include"DebugLogSystem.h"

using namespace HandyItems::Debug;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// ログ送信関数
/// </summary>
/// <param name="data">送るログデータ</param
void DebugLogSystem::send_to_thread(
	const LogObject& data
) {

	//	ログスレッドに送信
	log_thread->insert_LogObject(data);
}

/* ========== Privateメンバー関数 ========== */

/// <summary>
///	コンストラクタ
/// </summary>
DebugLogSystem :: DebugLogSystem() {
	log_thread = std::make_unique<DebugLogThread>();
}

/// <summary>
/// デストラクタ
/// </summary>
DebugLogSystem :: ~DebugLogSystem() = default;