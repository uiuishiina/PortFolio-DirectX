
struct VSInput
{
    float3 pos : POSITION;
};

struct VSoutput
{
    float4 pos : SV_POSITION;
};

VSoutput main(VSInput input)
{
    VSoutput output;
    
    output.pos = float4(input.pos, 1.0f);

    return output;
}