
/* ========== Includeファイル ========== */

#include"DirectXUpdater.h"
#include"ClassModule/FrameContext.h"

using namespace DirectX;

/* ========== Publicメンバー関数 ========== */

/* ===== 実行関数 ===== */

[[nodiscard]] bool DirectXUpdator::begin_update() {

	return true;
}

void DirectXUpdator::sync_frame_resource() {

	const auto wait = context_->frame_resources[current_index]->get_frame_value();

	//	使えるまで待機
	context_->fence_->wait_to_completed_value(wait);

}

void DirectXUpdator::reset_frame_resource() {

	//	コマンドアロケーター取得
	auto allocator = context_->frame_resources[current_index]->get_allocator();

	//	コマンドアロケータリセット
	allocator->reset_allocator();

	//	コマンドリストリセット
	context_->graphic_list->reset_list(allocator->get());
}

void DirectXUpdator::update() {

	const auto buffer_index = context_->swapchain_->get()->GetCurrentBackBufferIndex();

	auto frame = ClassModule::FrameContext{ context_, buffer_index, current_index };


	auto* back = frame.back_buffer;
	back->barrier_transition(frame.graphic_list->get(), D3D12_RESOURCE_STATE_RENDER_TARGET);

	float color[4] = { 1,1,1,1 };
	frame.graphic_list->get()->ClearRenderTargetView(back->get_RTV_handle(), color, 0, nullptr);

	back->barrier_transition(context_->graphic_list->get(), D3D12_RESOURCE_STATE_PRESENT);

	//for (auto& pass : pass_order) {
	//	pass->apply_pass(frame);
	//}

}

void DirectXUpdator::execute_command_lists() {

	//	コマンドリストをクローズ
	context_->graphic_list->get()->Close();

	//	コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { context_->graphic_list->get() };
	context_->graphic_queue->get()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//	シグナルを送って配列に保存
	context_->frame_resources[current_index]->end_frame_signal(context_->graphic_queue->get());

}

void DirectXUpdator::present() {

	context_->swapchain_->get()->Present(1, 0);

}

void DirectXUpdator::end_update() {

	current_index++;
}