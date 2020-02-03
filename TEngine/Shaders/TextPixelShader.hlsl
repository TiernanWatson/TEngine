texture2D<float> texDiffuse;
SamplerState sampleType;

float4 main(float2 texCoord : TEXCOORD) : SV_TARGET
{
	return float4(1.f, 1.f, 1.f, texDiffuse.Sample(sampleType, texCoord));
}