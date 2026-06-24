#include"DebugLogOutPut.h"

//出力用
#define WIN32_LEAN_AND_MEAN	//軽量化マクロ
#include <windows.h>

///====================================================================
/// Publicメンバー関数
///====================================================================

//@brief	=== 出力文字列受付関数 ===
//@param	log	LogObject構造体
void DebugLogOutPut:: ReceptionLog(const LogObject& log) {

	//末尾改行を追加して出力
	OutPutLog(log.LogData + "\n");
}

///====================================================================
/// Privateメンバー関数
///====================================================================

//@brief	=== 出力本体関数 ===
//@param	log	Log文字列
void DebugLogOutPut:: OutPutLog(const std::string& log) {
	OutputDebugStringA(log.c_str());
}