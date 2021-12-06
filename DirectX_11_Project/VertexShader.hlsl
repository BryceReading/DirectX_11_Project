//** Shaders should always end in hlsl (high level shader language) **// 

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
    outP.posOut = float4(input.posIn, 1.0f);
    outP.texCoordOut = input.texCoordIn;
    return outP;
}
