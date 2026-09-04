#include"DirectXUpdater.h"
#include"DirectXInitializer.h"

#include"../../Debug/DebugLogSystem.h"

using namespace render::dx12;

/* ==================================================================== */
/// 無名空間
/* ==================================================================== */

namespace {

	/// <summary>
	/// フレームリソースインデックス確認フラグ
	/// </summary>
	const bool frame_index_flag = false;
};

/* ==================================================================== */
// 初期化間数
/* ==================================================================== */

/// <summary>
/// 引数付きコンストラクタ
/// </summary>
/// <param name="context">DirectX描画機能インスタンス保存クラス参照</param>
DirectXUpdater::DirectXUpdater(DirectXRendererContext* context) {

	//	参照を保存
	context_ = context;

	//	フレームリソースサイズを取得
	frame_resouse_size = context_->frame_resources.size();
}

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* ==================== 描画更新前 ==================== */

/// <summary>
/// 描画更新前関数
/// </summary>
/// <returns>DirectX描画機能インスタンスが破棄されていた場合 [ false ] 破棄されていないなら [ true ]</returns>
[[nodiscard]] bool DirectXUpdater::begin_update_renderer() {

	//	nullチェック
	if (context_ == nullptr) {
		DEBUG_ERROR_LOG("DirectXUpdater :: context_ nullptr\n", "frame_count = ", std::to_string(frame_count));
		return false;
	}

	frame_count++;

	return true;
}

/* ==================== 描画更新中 ==================== */

/// <summary>
/// フレームリソース使用可能確認関数
/// </summary>
/// <details>
/// フレームリソースが使用可能な状態か確認する関数
/// </details>
void DirectXUpdater::sync_frame_resource() {

	//	これから使うフレームリソースが使える状態か判断
	auto value = context_->frame_resources[current_frame_index]->get_frame_fence_value();
	auto complete = context_->fence_->get_completed_value();
	if (value > complete) {

		//	使えるまで待機
		context_->fence_->wait_to_completed_value(value);
	}

	//	frame_count = 現在フレームの値 : complete_fence_value = GPU処理が終わったフェンスの値
	if (frame_index_flag) {
		DEBUG_LOG(
			"frame_count", std::to_string(frame_count), " : ",
			"complete_fence_value = ", std::to_string(value), " : ",
			"new_fence_value = ", std::to_string(context_->fence_->get_now_signal_value())
		);
	}
}

/// <summary>
/// フレームリソースリセット関数
/// </summary>
void DirectXUpdater::reset_frame_resource() {

	//コマンドアロケーター取得
	auto allocator = context_->frame_resources[current_frame_index]->get_graphics_allocator();

	// コマンドアロケータリセット
	allocator->reset_command_allocator();

	// コマンドリストリセット
	context_->graphics_list->reset_command_list(allocator->get_command_allocator());
}

/// <summary>
/// 描画パス呼び出し関数
/// </summary>
/// <details>
/// 作成した描画パスを呼び出す関数
/// </details>
/// <param name="pass_order">描画パス呼び出し順保存配列参照</param>
void DirectXUpdater::apply_draw_pass(std::vector<std::string>& pass_order) {


	//	描画リソース作成
	auto resources = DirectXInitializer::create_draw_resources(context_, current_frame_index);

	//	描画パス実行
	for (auto& name : pass_order) {
		context_->static_draw_pass_container->apply_draw_pass(name.c_str(), resources);
	}
}

/// <summary>
/// 描画コマンド送信関数
/// </summary>
/// <details>
/// コマンドリストに記録したコマンドを送信する
/// </details>
void DirectXUpdater::execute_command_lists() {

	// コマンドリストをクローズ
	context_->graphics_list->get_graphics_command_list()->Close();

	// コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { context_->graphics_list->get_graphics_command_list() };
	context_->graphics_queue->get_command_queue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//	シグナルを送って配列に保存
	context_->frame_resources[current_frame_index]->set_frame_fence_value(context_->fence_->signal(context_->graphics_queue->get_command_queue()));
}

/// <summary>
/// スワップチェーンプレゼント関数
/// </summary>
void DirectXUpdater::present() {

	// プレゼント
	context_->swap_chain->get_swapchain()->Present(1, 0);
}


/* ==================== 描画更新後 ==================== */

/// <summary>
/// 描画更新後関数
/// </summary>
void DirectXUpdater::end_update_renderer() {

	//	フレームリソースサイクルを進める
	current_frame_index = (current_frame_index + 1) % frame_resouse_size;
}


/* ==================== 描画終了時 ==================== */

/// <summary>
/// 描画機能終了時処理関数
/// </summary>
/// <details>
/// 内部でGPU同期チェック
/// </details>
void DirectXUpdater::end_updater() {

	//	GPUに投入済みのすべてのコマンドが完了するまで待機
	//	アプリケーション終了時は次フレームが存在しないため通常のフレーム同期ではなく終了用のFenceを使用する

	const auto signal = context_->fence_->signal(context_->graphics_queue->get_command_queue());
	context_->fence_->wait_to_completed_value(signal);

	//	最終フェンス確認用(GPU待機が完全にできているか)
	if (frame_index_flag) {

		//	フレームリソース待機インデックス確認
		DEBUG_LOG(
			"fence_value = ", 
			context_->frame_resources[0]->get_frame_fence_value()," : ",
			context_->frame_resources[1]->get_frame_fence_value()," : ",
			context_->frame_resources[2]->get_frame_fence_value()
		);
		//	上記の値の最大値より [ 1 ] 上なら正常
		DEBUG_LOG("last_fence_value = ", std::to_string(signal));
	}

	DEBUG_LOG("DirectXUpdater :: frame_count = ", frame_count);
}