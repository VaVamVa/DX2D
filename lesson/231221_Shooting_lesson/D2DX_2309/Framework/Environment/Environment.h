#pragma once

class Environment : public Singleton<Environment>
{
public:
    Environment();
    ~Environment();

private:
    void SetViewport();
    void SetProjection();

    void CreateSamplerState();
    void CreateBlendState();
    void CreateRasterizerState();

private:
    MatrixBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;

    ID3D11SamplerState* samplerState;
    ID3D11BlendState* blendState;
    ID3D11RasterizerState* rasterizerState;
};