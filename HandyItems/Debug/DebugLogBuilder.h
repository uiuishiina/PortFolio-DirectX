#pragma once
//	補助関数用
#include<concepts>
#include <sstream>

#include"LogObject.h"	//LogObject

///====================================================================
/// LogObject構造体作成補助関数
///====================================================================

//@brief	===  "<<" 変換可能コンセプト ===
template<typename T>
concept stream_insert_able = requires(std::ostream & os, const T & value) {

	//	os << value が std::ostream になるか
	{ os << value } -> std::same_as<std::ostream&>;
};

//@brief	=== string作成補助関数 ===
template<stream_insert_able... Args>
static [[nodiscard]] std::string create_string(Args&&... args) {

	//中央展開
	std::ostringstream oss;
	(oss << ... << std::forward<Args>(args));
	return oss.str();
}


///====================================================================
/// DebugLogBuilderクラス
///====================================================================

//@brief	=== デバッグログ構造体作成クラス ===
class DebugLogBuilder final
{
public:
	///====================================================================
	/// Publicメンバー関数
	///====================================================================

	//@brief	=== LogObject作成関数 ===
	//@param	data	データにしたい文字列
	//@return	作成されたLogObject
	static [[nodiscard]] LogObject create_LogObject(const std::string& data, LogLevel level = LogLevel::Info);

private:
	///====================================================================
	/// クラス設定
	///====================================================================

	//	コンストラクタ,デストラクタ
	DebugLogBuilder() = default;
	~DebugLogBuilder() = default;

	//	コピー,ムーブ禁止
	DebugLogBuilder(const DebugLogBuilder&) = delete;
	DebugLogBuilder& operator=(const DebugLogBuilder&) = delete;
	DebugLogBuilder(const DebugLogBuilder&&) = delete;
	DebugLogBuilder& operator=(const DebugLogBuilder&&) = delete;
};