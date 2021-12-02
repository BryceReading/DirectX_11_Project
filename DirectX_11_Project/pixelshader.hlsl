struct PS_INPUT
{
    float4 posIn : SV_POSITION;
    float3 colourIn : COLOUR;
};

float4 main(PS_INPUT inP) : SV_TARGET
{
    return float4(inP.colourIn, 1.0f);
}