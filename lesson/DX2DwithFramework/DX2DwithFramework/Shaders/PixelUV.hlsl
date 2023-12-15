// 2������ texture�� 3���� ���� ������ �ൿ : UV mapping
// Texture�� �ﰢ������ ������, 3���� ��ü�� ���δ�.
// texture�� ���� : u, texture�� ���� : v.
// �� uv ���� ���� 3���� ������ �����Ͽ�(mapping) ���̰� �ȴ�.

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Texture2D map : register(t0);  // Texture => t
SamplerState samp : register(s0);  // sampler => s

float4 PS(PixelInput input) : SV_TARGET
{
    return map.Sample(samp, input.uv);
}