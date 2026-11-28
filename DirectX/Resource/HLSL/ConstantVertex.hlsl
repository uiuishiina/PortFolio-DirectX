#include"StructHeader.hlsli"

VS_OutPutColor main(VS_InputColor input)
{
    VS_OutPutColor output;
   
    float4 pos = float4(input.pos, 1.0f);
    
    pos = mul(obj_transform, pos);
    pos = mul(view_, pos);
    pos = mul(projection_, pos);

    output.pos = pos;
    output.color = input.color;
    
    return output;
}