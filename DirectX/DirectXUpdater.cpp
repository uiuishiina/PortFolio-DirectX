
/* ========== Includeファイル ========== */

#include"DirectXUpdater.h"
#include"ClassModule/FrameContext.h"

using namespace DirectX;

/* ========== Publicメンバー関数 ========== */

/* ===== 実行関数 ===== */

[[nodiscard]] bool DirectXUpdator::begin_update() {

	++frame_count;

	//	このUpdateで利用するインデックスに変更する
	context_->back_buffer_index->update_index();
	context_->frame_resource_index->update_index();

	return true;
}

void DirectXUpdator::sync_frame_resource() {

	//	利用するインデックスから参照
	const auto wait = context_->frame_resources[context_->frame_resource_index->get_current_index()]
		->get_frame_value();

	//	使えるまで待機
	context_->fence_.wait_to_completed_value(wait);
}

void DirectXUpdator::reset_frame_resource() {

	//	フレームリソースリセット
	context_->frame_resources[context_->frame_resource_index->get_current_index()]->reset_frame_resource();

	//	コマンドアロケーター取得
	auto& allocator = context_->frame_resources[context_->frame_resource_index->get_current_index()]
		->get_allocator();

	//	コマンドリストリセット
	context_->graphic_list.reset_list(allocator.get());

}

void DirectXUpdator::update_resource() {

}

void DirectXUpdator::apply_path() {

	auto frame = ClassModule::FrameContext{ context_,frame_count };

	for (auto& pass : pass_order) {
		pass->apply_path(frame);
	}
}

void DirectXUpdator::execute_command_lists() {

	//	コマンドリストをクローズ
	context_->graphic_list->Close();

	//	コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { context_->graphic_list.get() };
	context_->graphic_queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//	シグナルを送って配列に保存
	context_->frame_resources[context_->frame_resource_index->get_current_index()]
		->end_frame_signal(context_->graphic_queue.get());
}

void DirectXUpdator::present() {

	context_->swapchain_->Present(1, 0);
}

void DirectXUpdator::end_update() {

}