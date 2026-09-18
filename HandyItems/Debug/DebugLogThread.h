#pragma once
#include<thread>					//スレッド用
#include<queue>						//log_queue用
#include<mutex>						//スレッドセーフ用
#include<condition_variable>		//スレッド通知用
#include"DebugLogOutPut.h"			//LogObject構造体,DebugLog出力

///====================================================================
/// DebugLogThreadクラス
///====================================================================

//@brief	=== DebugLog用スレッド管理クラス ===
class DebugLogThread final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	DebugLogThread();
	~DebugLogThread();

	//コピー,ムーブ削除
	DebugLogThread(const DebugLogThread&) = delete;
	DebugLogThread& operator= (const DebugLogThread) = delete;
	DebugLogThread(const DebugLogThread&&) = delete;
	DebugLogThread& operator= (const DebugLogThread&&) = delete;

	///====================================================================
	/// Publicメンバー関数
	///====================================================================

	//@breif	=== キュー登録関数 ===
	//@param	log	LogObject構造体
	void insert_LogObject(const LogObject& log);
private:
	///====================================================================
	/// Privateメンバー変数
	///====================================================================

	//@brief	== スレッドセーフ管理オブジェクト ==
	std::mutex queue_mutex{};

	//@brief	== スレッド通知用オブジェクト ==
	std::condition_variable_any cv{};

	//@breif	== DebugLogキュー ==
	std::queue<LogObject> log_queue{};

	//@brief	== DebugLog用スレッド ==
	std::jthread log_thread{};

	///====================================================================
	/// Privateメンバー関数
	///====================================================================

	//@brief	=== スレッド初期化関数 ===
	void initialize_thread();

	//@brief	=== デバッグ出力
	void send2DebugOutPut(const LogObject& log);
};