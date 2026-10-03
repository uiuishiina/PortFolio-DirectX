
/*
    Vertex
*/

struct VS_InputNormal
{
    float3 pos : POSITION;
};

struct VS_OutPutNormal
{
    float4 pos : SV_Position;
};

struct VS_InputColor
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VS_OutPutColor
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

/*
    Pixel
*/

struct PS_OutPut
{
    float4 color : SV_Target;
};