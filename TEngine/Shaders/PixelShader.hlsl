Texture2D texDiffuse;
SamplerState sampleType;

float4 main(float3 col : COLOR, float2 texCoord : TEXCOORD) : SV_TARGET
{
	return texDiffuse.Sample(sampleType, texCoord);
}