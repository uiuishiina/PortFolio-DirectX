#pragma once
#include<memory>			//	unique_ptr用
#include"DebugLogBuilder.h"		//	LogObject用

///====================================================================
/// ログ出力マクロ
///====================================================================

#ifdef _DEBUG

#define DEBUG_LOG(...) \
	do{\
		HandyItems::Debug::DebugLogSystem::Instance().send_to_thread(\
			HandyItems::Debug::DebugLogBuilder::create_LogObject(\
			HandyItems::Debug::create_string(__VA_ARGS__)\
		));\
	}while(0)

#define DEBUG_ERROR_LOG(...) \
	do{\
		HandyItems::Debug::DebugLogSystem::Instance().send_to_thread(\
			HandyItems::Debug::DebugLogBuilder::create_LogObject(\
			HandyItems::Debug::create_string(__VA_ARGS__),HandyItems::Debug::LogLevel::Error\
		));\
	}while(0)
#else

#define DEBUG_LOG(...) ((void)0)
#define DEBUG_ERROR_LOG(...) ((void)0)

#endif

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// デバッグ名前空間
	/// </summary>
	namespace Debug {

		/* ========== 前方宣言 ========== */

		class DebugLogThread;

		/// <summary>
		/// デバッグログシステムクラス
		/// </summary>
		class DebugLogSystem final
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// インスタンス取得関数
			/// </summary>
			/// <returns>DebugLogSysrtemインスタンス</returns>
			static DebugLogSystem& Instance() {
				static DebugLogSystem instance;
				return instance;
			}

			/// <summary>
			/// ログ送信関数
			/// </summary>
			/// <param name="data">送るログデータ</param>
			void send_to_thread(
				const LogObject& data
			);

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ログスレッドクラス
			/// </summary>
			std::unique_ptr<DebugLogThread> log_thread{};

			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DebugLogSystem();

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DebugLogSystem();

		};
	}
}