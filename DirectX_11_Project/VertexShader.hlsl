//** Shaders should always end in hlsl (high level shader language) **// 

cbuffer bufferC : register(b0)
{
    float4x4 mx;
};

struct VS_INPUT
{
    float3 posIn : POSITION;
    float2 texCoordIn : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 posOut : SV_POSITION;
    float2 texCoordOut : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT outP;
    outP.posOut = mul(float4(input.posIn, 1.0f), mx);
    outP.texCoordOut = input.texCoordIn;
    return outP;
}
