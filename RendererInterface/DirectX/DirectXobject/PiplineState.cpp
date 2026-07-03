#include "PiplineState.h"
#include"../PiplineStateHelper.h"

[[nodiscard]] HRESULT PiplineState::create_piplinestate(ID3D12Device* device, PipelineStateDesc& desc)
{
    PipelineStateDesc default_desc = PiplineStateHepler::default_pipline_desc();
    
}