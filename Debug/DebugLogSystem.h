#pragma once
#include<memory>			//	unique_ptr用
#include"DebugLogBuilder.h"		//	LogObject用

///====================================================================
/// ログ出力マクロ
///====================================================================

#ifdef _DEBUG

#define DEBUG_LOG(...) \
	do{\
		DebugLogSystem::Instance().send2thread(DebugLogBuilder::create_LogObject(create_string(__VA_ARGS__)));\
	}while(0)

#define DEBUG_ERROR_LOG(...) \
	do{\
		DebugLogSystem::Instance().send2thread(DebugLogBuilder::create_LogObject(create_string(__VA_ARGS__),LogLevel::Error));\
	}while(0)
#else

#define DEBUG_LOG(...) ((void)0)
#define DEBUG_ERROR_LOG(...) ((void)0)

#endif

///====================================================================
/// 前方宣言
///====================================================================

class DebugLogThread;

///====================================================================
/// DebugLogSystemクラス
///====================================================================

//@brief	=== デバッグログシステムクラス ===
class DebugLogSystem final
{
public:
	///====================================================================
	/// Publicメンバー関数
	///====================================================================

	//@brief	=== インスタンス取得関数 ===
	//@return	DebugLogSysrtemインスタンス
	static DebugLogSystem& Instance() {
		static DebugLogSystem instance;
		return instance;
	}

	//@breif	=== ログ送信関数 ===
	//@param	data	送るログデータ
	void send2thread(const LogObject& data);

private:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	DebugLogSystem();
	~DebugLogSystem();

	//	コピー,ムーブ禁止
	DebugLogSystem(const DebugLogSystem&) = delete;
	DebugLogSystem& operator=(const DebugLogSystem&) = delete;
	DebugLogSystem(const DebugLogSystem&&) = delete;
	DebugLogSystem& operator=(const DebugLogSystem&&) = delete;

	///====================================================================
	/// Privateメンバー変数
	///====================================================================

	//@brief	== ログスレッドクラス ==
	std::unique_ptr<DebugLogThread> log_thread{};
};