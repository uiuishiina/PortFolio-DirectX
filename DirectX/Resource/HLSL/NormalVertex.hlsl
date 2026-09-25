
#include"StructHeader.hlsli"

VS_OutPutNormal main( VS_InputNormal input )
{
	
    VS_OutPutNormal output;
    output.pos = float4(input.pos, 1.0f);
    
    return output;
}