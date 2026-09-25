
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


/*
    Pixel
*/

struct PS_OutPutNormal
{
    float4 color : SV_Target;
};