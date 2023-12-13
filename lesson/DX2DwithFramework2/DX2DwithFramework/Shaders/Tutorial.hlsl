//Tutorial.hlsl

// �ݷ� �� �̸� == Sementic : �Ű����� �� ��ȯ�� ������ ��� ������� �̸� ���̴� ��
// SV : System Value : �츮�� ¥�� �ʴ� ��ũ��Ʈ���� System�̶� �����ϸ� ����.

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
    
    // wvp ��ȯ
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