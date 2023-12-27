struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

Texture2D map : register(t0);
Texture2D secondMap : register(t1);

SamplerState samp : register(s0);

cbuffer AngleBuffer : register(b0)
{
	float angle;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float2 coord = input.uv - float2(0.5f, 0.5f);
	float2 uv;
	uv.x = coord.x * cos(angle) - coord.y * sin(angle);
	uv.y = -(coord.x * sin(angle) + coord.y * cos(angle));

	float4 tex1 = map.Sample(samp, input.uv);
	float4 tex2 = secondMap.Sample(samp, uv) * 2.0f;

	return tex1 * tex2;
}