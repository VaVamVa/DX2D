#include "framework.h"

std::unordered_map<std::wstring, PixelShader*> PixelShader::pixelShaders;

PixelShader::PixelShader(ID3D11PixelShader* shader)
    :shader(shader)
{
}

PixelShader::~PixelShader()
{
    shader->Release();
}

PixelShader* PixelShader::Add(std::wstring file)
{
    std::unordered_map<std::wstring, PixelShader*>::iterator iter = pixelShaders.find(file);
    if (iter != pixelShaders.end())
        return iter->second;

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* pixelBlob;  // buffer -> shader 데이터 변환용 (데이터 주소 및 크기 정보용 인터페이스)
    // 4번째 매개변수 : 진입점
    D3DCompileFromFile(
        file.c_str(), nullptr, nullptr,
        "PS", "ps_5_0", flags,
        0, &pixelBlob, nullptr
    );

    ID3D11PixelShader* shader;
    DEVICE->CreatePixelShader(
        pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(),
        nullptr, &shader
    );

    pixelBlob->Release();

    PixelShader* newPixelShader = new PixelShader(shader);
    pixelShaders.insert({ file, newPixelShader });

    return newPixelShader;
}

void PixelShader::Set()
{
	DC->PSSetShader(shader, nullptr, 0);
}

void PixelShader::Destroy()
{
    std::unordered_map<std::wstring, PixelShader*>::iterator iter;
    
    for (iter = pixelShaders.begin(); iter != pixelShaders.end(); iter++)
    {
        delete iter->second;
    }
    pixelShaders.clear();
}
