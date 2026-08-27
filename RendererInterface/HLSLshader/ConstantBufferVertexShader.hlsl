struct VSInput
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VSoutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

cbuffer CameraBuffer : register(b0)
{
    matrix transform_;
    matrix view_;
    matrix projection_;
};

VSoutput main(VSInput input)
{
    VSoutput output;
    
    float4 pos = float4(input.pos, 1.0f);
    
    
    pos = mul(pos, transpose(transform_));
    pos = mul(pos, transpose(view_));
    pos = mul(pos, transpose(projection_));
    
   
    output.pos = pos;
    output.color = input.color;

    return output;
}