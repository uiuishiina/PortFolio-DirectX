#include "DrawRenderTargetState.h"

using namespace render::state;

///====================================================================
/// 初期化時処理関数
///====================================================================

//@brief	=== 描画先設定追加関数 ===
//@param	slot	追加するターゲットの種類
void DrawRenderTargetState::add_render_target_slot(RenderTargetSlot slot) {
	render_targets_slot.push_back(slot);
}

//@brief	=== デプスバッファ設定関数 ===
//@param	slot	設定するDSVの種類
void DrawRenderTargetState::set_depth(DepthSlot slot) {
	depth_slot = slot;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 描画パス実行時レンダーターゲットバインド関数 ==
void DrawRenderTargetState::apply(resouces::DrawResouces& resouce) {

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handles_{};
	D3D12_CPU_DESCRIPTOR_HANDLE dsv_{};

	for (auto& p : render_targets_slot) {
		handles_.push_back(resouce.get_target(p)->get_rtv_handle());
	}
	if (depth_slot.has_value()) {
		resouce.graphics_list->OMSetRenderTargets(1, handles_.data(), false, &dsv_);
	}
	else {
		resouce.graphics_list->OMSetRenderTargets(1, handles_.data(), false, nullptr);
	}
}