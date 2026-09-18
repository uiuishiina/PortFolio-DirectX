#include"DebugLogBuilder.h"

///====================================================================
/// 無名空間
///====================================================================

namespace {
	//	罫線
	std::string Gridlines = std::string(100, '-');

	//	改行
	std::string LineBreak = "\n";

	//	見やすくするようまとめ
	std::string ErrorLine = Gridlines + LineBreak;
}

///====================================================================
/// Publicメンバー関数
///====================================================================

//@brief	=== LogObject作成関数 ===
//@param	data	データにしたい文字列
//@return	作成されたLogObject
[[nodiscard]] LogObject DebugLogBuilder :: create_LogObject(const std::string& data, LogLevel level) {

	//	エラーログなら
	if (level == LogLevel::Error) {
		auto str = create_string(ErrorLine + data + LineBreak + Gridlines);
		return LogObject(std::move(str));
	}
	else {
		//	そのまま作成
		return LogObject(data);
	}
}