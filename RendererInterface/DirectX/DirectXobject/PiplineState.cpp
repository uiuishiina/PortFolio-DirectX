#include "PiplineState.h"
#include"../PiplineStateHelper.h"

PipelineStateDesc::PipelineStateDesc() {

    rasterizer_desc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    blend_desc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    depth_stencil_desc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
}

[[nodiscard]] HRESULT PiplineState::create_piplinestate(ID3D12Device* device, PipelineStateDesc& desc)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_desc{};

    // Input Layout
    pipeline_desc.InputLayout = { desc.input_elements.data(), static_cast<UINT>(desc.input_elements.size()) };

    // Root Signature
    pipeline_desc.pRootSignature = desc.root_signature;

    // Shader
    if (desc.vs_hlsl) {
        pipeline_desc.VS = { desc.vs_hlsl->GetBufferPointer(),desc.vs_hlsl->GetBufferSize() };
    }

    if (desc.ps_hlsl){
        pipeline_desc.PS = { desc.ps_hlsl->GetBufferPointer(),desc.ps_hlsl->GetBufferSize() };
    }

    if (desc.gs_hlsl) {
        pipeline_desc.GS = { desc.gs_hlsl->GetBufferPointer(),desc.gs_hlsl->GetBufferSize() };
    }

    if (desc.hs_hlsl){
        pipeline_desc.HS = { desc.hs_hlsl->GetBufferPointer(),desc.hs_hlsl->GetBufferSize() };
    }

    if (desc.ds_hlsl) {
        pipeline_desc.DS = { desc.ds_hlsl->GetBufferPointer(),desc.ds_hlsl->GetBufferSize() };
    }

    // State
    pipeline_desc.RasterizerState = desc.rasterizer_desc;
    pipeline_desc.BlendState = desc.blend_desc;
    pipeline_desc.DepthStencilState = desc.depth_stencil_desc;

    // Primitive
    pipeline_desc.PrimitiveTopologyType = desc.primitive_topology;

    // Render Target
    pipeline_desc.NumRenderTargets = desc.num_render_targets;
    for (UINT i = 0; i < desc.num_render_targets; ++i) {
        pipeline_desc.RTVFormats[i] = desc.rtv_formats[i];
    }

    pipeline_desc.DSVFormat = desc.dsv_format;

    // Multi Sampling
    pipeline_desc.SampleDesc.Count = desc.sample_count;
    pipeline_desc.SampleDesc.Quality = desc.sample_quality;

    // Sample Mask
    pipeline_desc.SampleMask = desc.sample_mask;

    // Misc
    pipeline_desc.NodeMask = desc.node_mask;
    pipeline_desc.Flags = desc.flags;
    
    const auto hr = device->CreateGraphicsPipelineState(&pipeline_desc, IID_PPV_ARGS(&pipline_state));
    if (FAILED(hr)) {
        return hr;
    }
    return S_OK;
}