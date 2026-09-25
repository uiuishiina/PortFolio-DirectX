
/* ========== Includeファイル ========== */

#include"PiplineStateHelper.h"

#include"../External/d3dx12.h"

using namespace DirectX::Helper;

/* ========== Publicメンバー関数 ========== */

/* ===== 取得関数 ===== */

/* -- デフォルト関数 -- */

/// <summary>
/// デフォルトラスタライザー設定作成関数
/// </summary>
/// <returns>デフォルトラスタライザー設定</returns>
[[nodiscard]] D3D12_RASTERIZER_DESC PiplineStateHelper::default_rasterizer() {

    return CD3DX12_RASTERIZER_DESC{ D3D12_DEFAULT };
}

/// <summary>
/// デフォルトブレンド設定作成関数
/// </summary>
/// <returns>デフォルトブレンド設定</returns>
[[nodiscard]] D3D12_BLEND_DESC PiplineStateHelper::default_blend() {

    return CD3DX12_BLEND_DESC{ D3D12_DEFAULT };
}

/// <summary>
/// デフォルトデプス設定作成関数
/// </summary>
/// <returns>デフォルトデプス設定</returns>
[[nodiscard]] D3D12_DEPTH_STENCIL_DESC PiplineStateHelper::default_depth() {
    
    auto depth = CD3DX12_DEPTH_STENCIL_DESC{ D3D12_DEFAULT };

    depth.DepthEnable = FALSE;

    return depth;
}

/* -- 有効化関数 -- */

/// <summary>
/// ブレンド有効化設定作成関数
/// </summary>
/// <returns>ブレンド有効化設定</returns>
[[nodiscard]] D3D12_BLEND_DESC PiplineStateHelper::enable_blend() {

    auto desc = default_blend();

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

/// <summary>
/// デプス有効化設定作成関数
/// </summary>
/// <returns>デプス有効化設定</returns>
[[nodiscard]] D3D12_DEPTH_STENCIL_DESC PiplineStateHelper::enable_depth() {

    auto desc = default_depth();

    desc.DepthEnable = TRUE;

    //  比較方法
    desc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

    return desc;
}