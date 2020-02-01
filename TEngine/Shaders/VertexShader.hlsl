struct Ver2Pix
{
	float3 col : COLOR;
	float2 texCoord : TEXCOORD;
	float4 pos : SV_POSITION;
};

cbuffer Consts
{
	matrix model;
	matrix view;
	matrix proj;
};

Ver2Pix main( float3 pos : POSITION, float3 tangent : TANGENT, float2 texCoord : TEXCOORD )
{
	Ver2Pix toPix;
	toPix.col = float3(0.5f, 0.2f, 0.7f);

	toPix.pos = float4(mul(model, float4(pos, 1.f)));
	toPix.pos = float4(mul(view, toPix.pos));
	toPix.pos = float4(mul(proj, toPix.pos));

	toPix.texCoord = texCoord;

	return toPix;
}