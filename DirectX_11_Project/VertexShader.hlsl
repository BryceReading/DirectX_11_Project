//** Shaders should always end in hlsl (high level shader language) **// 

float4 main(float2 pos : POSITION) : SV_POSITION
{
	return float4(pos, 0, 1);
}
