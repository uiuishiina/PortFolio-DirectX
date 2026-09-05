#include "DrawRenderTargetState.h"

using namespace render::dx12::state;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 設定関数 -- */

/// <summary>
/// 描画先設定追加関数
/// </summary>
/// <param name="slot">追加する描画先設定</param>
void DrawRenderTargetState::add_render_target_slot(RenderTargetSlot slot) {
	render_targets_slot.push_back(slot);
}

/// <summary>
/// デプスバッファ設定関数
/// </summary>
/// <param name="slot">設定するデプスバッファ設定</param>
void DrawRenderTargetState::set_depth(DepthSlot slot) {
	depth_slot = slot;
}


/* -- 実行関数 -- */

/// <summary>
/// 描画パス実行時レンダーターゲットバインド関数
/// </summary>
/// <param name="resouce">描画リソース構造体参照</param>
void DrawRenderTargetState::apply(resources::DrawResources& resouce) {

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handles_{};
	
	for (auto& p : render_targets_slot) {
		handles_.push_back(resouce.get_render_target(p)->get_rtv_handle());
	}
	if (depth_slot.has_value()) {
		const auto dsv_ = resouce.frame_resource->depth_buffer->get_dsv_handle();
		resouce.graphics_list->OMSetRenderTargets(1, handles_.data(), false,&dsv_);
	}
	else {
		resouce.graphics_list->OMSetRenderTargets(1, handles_.data(), false, nullptr);
	}
}