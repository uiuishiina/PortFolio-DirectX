#include"StructHeader.hlsli"

VS_OutPutColor main(VS_InputColor input)
{
    VS_OutPutColor output;
    
    output.pos = float4(input.pos, 1.0f);
    output.color = input.color;
    
    return output;
}