cbuffer Consts
{
	matrix projection;
};

struct TextVertIn
{
	float3 pos : POSITION;
	float3 tangent : TANGENT;
	float2 texCoord : TEXCOORD;
};

struct Vert2Pix
{
	float2 texCoord : TEXCOORD;
	float4 pos : SV_POSITION;
};

Vert2Pix main(TextVertIn vertIn)
{
	Vert2Pix toPix;
	toPix.pos = mul(projection, float4(vertIn.pos.x, vertIn.pos.y, 0.f, 1.f));
	toPix.texCoord = vertIn.texCoord;

	return toPix;
}