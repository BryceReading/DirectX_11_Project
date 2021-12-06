struct PS_INPUT
{
    float4 posIn : SV_POSITION;
    float2 texCoordIn : TEXCOORD;
};

Texture2D objectTex : TEXTURE : register(t0);
SamplerState objectSS : SAMPLER : register(s0);

float4 main(PS_INPUT inP) : SV_TARGET
{
    float3 pixColor = objectTex.Sample(objectSS, inP.texCoordIn);
    return float4(pixColor, 1.0f);
}