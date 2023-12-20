#pragma once

class VertexShader : public Shader
{
private:
    friend class Shader;

    VertexShader(std::wstring file);
    ~VertexShader();

    void CreateInputLayout();

public:
    virtual void Set() override;

private:
    ID3D11VertexShader* shader;
    ID3D11InputLayout* inputLayout;

    ID3D11ShaderReflection* reflection;
};