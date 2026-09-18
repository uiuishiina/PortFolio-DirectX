#include"DebugLogThread.h"

///====================================================================
/// クラス設定
///====================================================================

//  コンストラクタ
DebugLogThread :: DebugLogThread() {

    //  スレッド初期化
    initialize_thread();
}

//  デストラクタ
DebugLogThread :: ~DebugLogThread() = default;

///====================================================================
/// Publicメンバー関数
///====================================================================

//@breif	=== キュー登録関数 ===
//@param	log	LogObject構造体
void DebugLogThread :: insert_LogObject(const LogObject& log) {

    //  Lockして競合を回避
    {
        std::lock_guard lock(queue_mutex);
        log_queue.push(log);
    }

    //  追加をthreadに通知
    cv.notify_one();
}

///====================================================================
/// Privateメンバー関数
///====================================================================

//@brief	=== スレッド初期化関数 ===
void DebugLogThread :: initialize_thread() {

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
            send2DebugOutPut(log);
        }

        //  スレッド終了ログ
        DebugLogOutPut::ReceptionLog(LogObject("DebugLogThread End"));
    });
}

//@brief	=== デバッグログ出力 ===
void DebugLogThread :: send2DebugOutPut(const LogObject& log) {

    //  出力クラス呼び出し
    DebugLogOutPut::ReceptionLog(log);
}