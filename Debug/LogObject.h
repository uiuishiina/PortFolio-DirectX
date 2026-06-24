#pragma once

//	構造体用
#include<string>
#include<string_view>

///====================================================================
/// LogObject構造体
///====================================================================
/// 作成意図としてしっかりオブジェクトに変換してから渡すということを明確に定義したいため
/// また、今後の拡張にも対応しやすいため
///====================================================================

//@brief	=== ログデータ構造体 ===
struct LogObject {

	//ログデータ
	std::string LogData{};

	LogObject() = default;
	//コンストラクタ
	LogObject(const std::string& str) :
		LogData(str) {};
};


//@brief	=== ログデーターレベル列挙体 ===
enum class LogLevel {
	Info,Error
};