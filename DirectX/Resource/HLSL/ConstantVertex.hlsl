#include"StructHeader.hlsli"

VS_OutPutNormal main(VS_InputNormal input)
{
    VS_OutPutNormal output;
   
    float4 pos = float4(input.pos, 1.0f);
    
    pos = mul(obj_transform, pos);
    pos = mul(view_, pos);
    pos = mul(projection_, pos);

    output.pos = pos;
    
    return output;
}