//Tutorial.hlsl
//Sementic : 매개변수 및 반환값 정보를 어떻게 사용할지 이름 붙이는 것
//SV : System Value

struct VertexInput
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

cbuffer WorldBuffer : register(b0)
{
	matrix world;
}

cbuffer ViewBuffer : register(b1)
{
	//matrix view;
	float4x4 view;
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
	
	output.color = input.color;
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return input.color;
}