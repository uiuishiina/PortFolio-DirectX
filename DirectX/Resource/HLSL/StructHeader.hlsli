
/*
    Vertex
*/

/* == Input == */

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


/* == ConstantBuffer == */

cbuffer CameraBuffer : register(b0)
{
    matrix view_;
    matrix projection_;
};

cbuffer ObjectTransform : register(b1)
{
    matrix obj_transform;
};

/*
    Pixel
*/

struct PS_OutPut
{
    float4 color : SV_Target;
};