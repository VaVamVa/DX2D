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

/*
cbuffer == constant buffer : 하지만 매우 동적으로 데이터가 변하는데,
쉐이더의 입장(쉐이더 연산 중)에는 상수처럼 변하지 않는 수 이기 때문.
*/
cbuffer WorldBuffer : register(b0) // buffer slot
{
    matrix world;
    // matrix == float4x4 : 4*4 행렬
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