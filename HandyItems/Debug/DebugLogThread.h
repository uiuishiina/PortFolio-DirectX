#pragma once

/* ========== Includeファイル ========== */

#include<thread>					//スレッド用
#include<queue>						//log_queue用
#include<mutex>						//スレッドセーフ用
#include<condition_variable>		//スレッド通知用
#include"DebugLogOutPut.h"			//LogObject構造体,DebugLog出力

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// デバッグ名前空間
	/// </summary>
	namespace Debug {

		/// <summary>
		/// DebugLog用スレッド管理クラス
		/// </summary>
		class DebugLogThread final
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DebugLogThread() {

				//  スレッド初期化
				initialize_thread();
			}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DebugLogThread() = default;


			/* ===== 実行関数 ===== */

			/// <summary>
			/// キュー登録関数
			/// </summary>
			/// <param name="log">LogObject構造体</param>
			void insert_LogObject(
				const LogObject& log
			) {

				//  Lockして競合を回避
				{
					std::lock_guard lock(queue_mutex);
					log_queue.push(log);
				}

				//  追加をthreadに通知
				cv.notify_one();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// スレッドセーフ管理オブジェクト
			/// </summary>
			std::mutex queue_mutex{};

			/// <summary>
			/// スレッド通知用オブジェクト
			/// </summary>
			std::condition_variable_any cv{};

			/// <summary>
			/// DebugLogキュー
			/// </summary>
			std::queue<LogObject> log_queue{};

			/// <summary>
			/// DebugLog用スレッド
			/// </summary>
			std::jthread log_thread{};


			/* ========== Privateメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// スレッド初期化関数
			/// </summary>
			void initialize_thread() {

				//  jthreadをラムダで作成
				//  初期化でデバッグ用スレッド(今はLogのみ)を作成し [デバッグ機能が終了するまで] 動く
				log_thread = std::jthread([this](std::stop_token st) {

					//  デストラクタで [stop] が送られてくるまでループ
					while (true)
					{
						//Lockを早く外すためにスコープの外側で宣言
						LogObject log{};
						{
							//  Lockして競合を回避
							std::unique_lock lock(queue_mutex);

							//  log_queueに [LogObject] が入ってくるまで停止
							//  デストラクタで [notify_all] が呼ばれるため [永久停止] にはならない
							cv.wait(lock, st, [this] {
								return !log_queue.empty();
								});

							//  [stop] かつ [log_queueの中身が空] なら終了
							if (st.stop_requested() && log_queue.empty()) {
								break;
							}

							//   [LogObject] 取り出し
							log = std::move(log_queue.front());
							log_queue.pop();
						}

						//  ログ出力
						send_to_debug_output(log);
					}

					//  スレッド終了ログ
					DebugLogOutPut::reception_log(LogObject("DebugLogThread End"));
					});
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// デバッグ出力
			/// </summary>
			/// <param name="log">LogObject構造体</param>
			void send_to_debug_output(
				const LogObject& log
			) {

				//  出力クラス呼び出し
				DebugLogOutPut::reception_log(log);
			}
		};
	}
}