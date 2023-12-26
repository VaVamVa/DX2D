struct VertexInput
{
	float4 pos : POSITION;	
};

struct PixelInput
{
	float4 pos : SV_POSITION;	
};

cbuffer WorldBuffer : register(b0)
{
	matrix world;
}

cbuffer ViewBuffer : register(b1)
{
	matrix view;
}

cbuffer ProjectionBuffer : register(b2)
{
	matrix projection;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	return output;
}