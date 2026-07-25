#include"PiplineStateHelper.h"

using namespace render::dx12::helper;

///====================================================================
/// 初期化関数
///====================================================================

[[nodiscard]] D3D12_BLEND_DESC PiplineStateHepler::get_enable_blend() {
	
    D3D12_BLEND_DESC desc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

    auto& rt = desc.RenderTarget[0];

    rt.BlendEnable = TRUE;
    rt.SrcBlend = D3D12_BLEND_SRC_ALPHA;
    rt.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
    rt.BlendOp = D3D12_BLEND_OP_ADD;
    rt.SrcBlendAlpha = D3D12_BLEND_ONE;
    rt.DestBlendAlpha = D3D12_BLEND_ZERO;
    rt.BlendOpAlpha = D3D12_BLEND_OP_ADD;

	return desc;
}