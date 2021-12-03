//** Shaders should always end in hlsl (high level shader language) **// 

struct VS_INPUT
{
    float3 posIn : POSITION;
    float3 colourIn : COLOUR;
};

struct VS_OUTPUT
{
    float4 posOut : SV_POSITION;
    float3 colourOut : COLOUR;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT outP;
    outP.posOut = float4(input.posIn, 1.0f);
    outP.colourOut = input.colourIn;
    return outP;
}
