#include"DebugLogThread.h"	//	DebugLogThread用
#include"DebugLogSystem.h"

///====================================================================
/// クラス設定
///====================================================================

//	コンストラクタ
DebugLogSystem :: DebugLogSystem() {
	log_thread = std::make_unique<DebugLogThread>();
}

//	デストラクタ
DebugLogSystem :: ~DebugLogSystem() = default;

///====================================================================
/// Publicメンバー関数
///====================================================================

//@breif	=== ログ送信関数 ===
//@param	data	送るログデータ
void DebugLogSystem :: send2thread(const LogObject& data) {

	//	ログスレッドに送信
	log_thread->insert_LogObject(data);
}