#include "DirectXUpdater.h"

#include"../../Debug/DebugLogSystem.h"

using namespace render::dx12;

///====================================================================
/// 初期化間数
///====================================================================

//@brief	=== 引数付きコンストラクタ ===
//@param	context	DirectX描画機能インスタンス保存クラス参照
DirectXUpdater::DirectXUpdater(DirectXRendererContext* context) {

	//	参照を保存
	context_ = context;

	//	フレームリソースサイズを取得
	frame_resouse_size = context_->frame_resources.size();
}

///====================================================================
/// 実行時処理関数群
///====================================================================

/* ==================== 描画更新前 ==================== */

//@brief	=== 描画更新前関数 ===
//@return	DirectX描画機能インスタンスが破棄されていた場合 [ false ] 破棄されていないなら [ true ]
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

//@brief	=== フレームリソース使用可能確認関数 ===
//@details	フレームリソースが使用可能な状態か確認する関数
void DirectXUpdater::sync_frame_resource() {

	//	これから使うフレームリソースが使える状態か判断
	auto value = context_->frame_resources[current_frame_index]->get_frame_fence_value();
	auto complete = context_->fence_->get_completed_value();
	if (value > complete) {

		//	使えるまで待機
		context_->fence_->wait_to_completed_value(value);
	}
}

//@brief	=== フレームリソースリセット関数 ===
//@details	フレームリソース内のリセットが必要なものをリセット
void DirectXUpdater::reset_frame_resource() {

	//コマンドアロケーター取得
	auto allocator = context_->frame_resources[current_frame_index]->get_graphics_allocator();

	// コマンドアロケータリセット
	allocator->reset_command_allocator();
	// コマンドリストリセット
	context_->graphics_list->reset_command_list(allocator->get_command_allocator());
}

//@breif	=== 描画パス呼び出し関数 ===
//@detais	作成した描画パスを呼び出す関数
//@param	pass_order	描画パス呼び出し順保存配列参照
void DirectXUpdater::apply_draw_pass(std::vector<std::string>& pass_order) {


	//	描画リソース作成
	auto resources = create_draw_resources();

	//	描画パス実行
	for (auto& name : pass_order) {
		context_->static_draw_pass_container->apply_draw_pass(name, resources);
	}
}

//@brief	=== 描画コマンド送信関数 ===
//@details	コマンドリストに記録したコマンドを送信する
void DirectXUpdater::execute_command_lists() {

	// コマンドリストをクローズ
	context_->graphics_list->get_graphics_command_list()->Close();

	// コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { context_->graphics_list->get_graphics_command_list() };
	context_->graphics_queue->get_command_queue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//	シグナルを送って配列に保存
	context_->frame_resources[current_frame_index]->set_frame_fence_value(context_->fence_->signal(context_->graphics_queue->get_command_queue()));
}

//@brief	=== スワップチェーンプレゼント関数 ===
void DirectXUpdater::present() {

	// プレゼント
	context_->swap_chain->get_swapchain()->Present(1, 0);
}


/* ==================== 描画更新後 ==================== */

//@brief	=== 描画更新後関数 ===
void DirectXUpdater::end_update_renderer() {

	//	フレームリソースサイクルを進める
	current_frame_index = (current_frame_index + 1) % frame_resouse_size;
}


/* ==================== 描画終了時 ==================== */

//@brief	=== 描画機能終了時処理関数 ===
//@details	内部でGPU同期チェック
void DirectXUpdater::destroy_updater() {

	//	すべてのフレームリソースが使われなくなるまで待機
	for (auto& value : context_->frame_resources) {
		context_->fence_->wait_to_completed_value(value->get_frame_fence_value());
	}

	DEBUG_LOG("DirectXUpdater :: frame_count = ", frame_count);
}


/* ==================== その他 ==================== */

//@brief	=== 描画リソース作成関数 ===
//@details	描画に利用するリソースをフレームごとにまとめて構造体にする関数
//@return	描画リソース構造体
[[nodiscard]] resources::DrawResources DirectXUpdater::create_draw_resources() {

	//	描画先のバッファインデックスを取得
	const auto backBufferIndex = context_->swap_chain->get_swapchain()->GetCurrentBackBufferIndex();

	//	描画リソースセット
	resources::DrawResources resources{};
	resources.graphics_list = context_->graphics_list->get_graphics_command_list();
	resources.frame_resource = context_->frame_resources[current_frame_index].get();
	resources.static_heap_container = context_->static_heap_container.get();
	resources.render_targets[resources::to_index(RenderTargetSlot::BackBuffer)] = context_->back_buffers[backBufferIndex].get();
	
	resources.mesh_[0] = context_->polygon_.get();
	resources.mesh_[1] = context_->Color_polygon_.get();

	return resources;
}