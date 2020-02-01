float4 main(float3 col : COLOR) : SV_TARGET
{
	return float4(col, 1.f);
}