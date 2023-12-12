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

PixelInput VS(VertexInput input) // Vertex Shader
{
    PixelInput output;
    output.pos = input.pos;
    output.color = input.color;
    
	return output;
}

float4 PS(PixelInput input) : SV_TARGET // Pixel Shader
{
    return input.color;
}