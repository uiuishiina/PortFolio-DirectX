#include "PiplineStateHelper.h"
#include"AddFile/d3dx12.h"

PipelineStateDesc PiplineStateHepler::default_pipline_desc()
{
    PipelineStateDesc desc{};

    desc.rasterizer_desc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    desc.blend_desc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    desc.depth_stencil_desc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

    return desc;
}