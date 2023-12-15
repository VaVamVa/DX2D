// 2차원의 texture를 3차원 세상에 입히는 행동 : UV mapping
// Texture를 삼각형으로 오리고, 3차원 물체에 붙인다.
// texture의 가로 : u, texture의 세로 : v.
// 이 uv 값에 따라 3차원 정점에 대응하여(mapping) 붙이게 된다.

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