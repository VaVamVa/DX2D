#include "framework.h"

PixelShader::PixelShader(std::wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* pixelBlob;
    // 4번째 매개변수 : 진입점
    D3DCompileFromFile(
        file.c_str(), nullptr, nullptr,
        "PS", "ps_5_0",
        flags, 0, &pixelBlob, nullptr
    );

    DEVICE->CreatePixelShader(
        pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(),
        nullptr, &shader
    );

    pixelBlob->Release();
}

PixelShader::~PixelShader()
{
    shader->Release();
}

void PixelShader::Set()
{
	DC->PSSetShader(shader, nullptr, 0);
}
