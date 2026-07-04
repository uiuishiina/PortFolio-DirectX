
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

VSoutput main(VSInput input)
{
    VSoutput output;
    
    output.pos = float4(input.pos, 1.0f);
    output.color = input.color;

    return output;
}