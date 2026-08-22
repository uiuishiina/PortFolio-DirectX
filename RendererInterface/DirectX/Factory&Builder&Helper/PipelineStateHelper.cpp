#include"PipelineStateHelper.h"

using namespace render::dx12::helper;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== ブレンド有効化設定作成関数 ===
//@return	ブレンド有効化設定
[[nodiscard]] D3D12_BLEND_DESC PipelineStateHelper::get_enable_blend() {
	
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

//@brief	=== デプス有効化設定作成関数 ===
//@return	デプス有効化設定
[[nodiscard]] D3D12_DEPTH_STENCIL_DESC PipelineStateHelper::get_enable_depth()
{
    D3D12_DEPTH_STENCIL_DESC desc =
        CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

    // Depth Test 有効
    desc.DepthEnable = TRUE;

    // Depth Bufferへの書き込み許可
    desc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;

    // 比較方法
    // 小さい値ほど手前なので LESS_EQUAL が一般的
    desc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;


    // Stencilは使用しない
    desc.StencilEnable = FALSE;


    return desc;
}