//Tutorial.hlsl

// 콜론 뒤 이름 == Sementic : 매개변수 및 반환값 정보를 어떻게 사용할지 이름 붙이는 것
// SV : System Value : 우리가 짜지 않는 스크립트들이 System이라 생각하면 편함.

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
    float4x4 view;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

PixelInput VS(VertexInput input) // Vertex Shader
{
    PixelInput output;
    
    // wvp 변환
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.color = input.color;
    
	return output;
}

float4 PS(PixelInput input) : SV_TARGET // Pixel Shader
{
    return input.color;
}