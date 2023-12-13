#include "framework.h"

VertexShader::VertexShader(std::wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* vertexBlob;
    D3DCompileFromFile(
        file.c_str(), nullptr, nullptr,
        "VS", "vs_5_0", flags,
        0, &vertexBlob, nullptr
    );

    DEVICE->CreateVertexShader(
        vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
        nullptr, &shader
    );

    D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize = ARRAYSIZE(layoutDesc);

    DEVICE->CreateInputLayout(
        layoutDesc, layoutSize,
        vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
        &inputLayout
    );

    vertexBlob->Release();
}

VertexShader::~VertexShader()
{
    shader->Release();
}

void VertexShader::Set()
{
    DC->IASetInputLayout(inputLayout);
    DC->VSSetShader(shader, nullptr, 0);
}
