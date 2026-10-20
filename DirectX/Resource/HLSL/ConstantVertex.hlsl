#include"StructHeader.hlsli"

VS_OutPutNormal main(VS_InputNormal input)
{
    VS_OutPutNormal output;
   
    float4 pos = float4(input.pos, 1.0f);
    
    pos = mul(pos, transpose(obj_transform));
    pos = mul(pos, transpose(view_));
    pos = mul(pos, transpose(projection_));
    
    output.pos = pos;
    
    return output;
}