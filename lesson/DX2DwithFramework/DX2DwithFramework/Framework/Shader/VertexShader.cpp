#include "framework.h"

std::unordered_map<std::wstring, VertexShader*> VertexShader::vertexShaders;

VertexShader::VertexShader(ID3D11InputLayout* inputLayout, ID3D11VertexShader* shader)
    :inputLayout(inputLayout), shader(shader)
{
}

VertexShader::~VertexShader()
{
    shader->Release();
    
}


/*
* ����� 6.1 p 210~213
struct D3D11_INPUT_ELEMENT_DESC
{
    LPCSTR SemanticName;
        ���̴����� �ǹ̼�(semantic) �̸�����, ���� ��Ȯ�ؾ� �ϸ� ���̴��� �Է� ����� �����Ǿ�� �Ѵ�.
        ���̴��� �ݷ� �ڿ� ���� �̸��� semantic name�̸�, �̿� inputLayout�� DESC�� SemanticName�� ���ƾ� �Ѵ�.

    UINT SemanticIndex;
        �ϳ��� ���� ����ü�� �ؽ�ó ��ǥ�� ���� �� �����ϴ� ��� �� �ؽ�ó ��ǥ�� �а��ϱ� ���� ����(index)
        ���̴� �ڵ忡�� semantic name �ٷ� �ڿ� ���ڷ� ǥ���ȴ�. (default 0)

    DXGI_FORMAT Format;
        inputLayout�� �ڷ� ���� ����

    UINT InputSlot;
        �ڷᰡ �Ҵ�� ���� ���� ������ ����. 16(0~15)���� ������ �����Ѵ�.

    UINT AlignedByteOffset;
        �Է� ������ �迭�� ���� ���, ���� ������ ũ�⸸ŭ byte�� �����Ͽ� ���� ������ �������� �����Ѵ�.

    D3D11_INPUT_CLASSIFICATION InputSlotClass;
        �ν��Ͻ̿� ��������, ����� `D3D11_INPUT_PER_VERTEX_DATA` �� �����Ѵ�.

    UINT InstanceDataStepRate;
        �ν��Ͻ̿� ��������, ����� `0` �� �����Ѵ�.
}

*/
VertexShader* VertexShader::Add(std::wstring file, D3D11_INPUT_ELEMENT_DESC layoutDesc[], int layoutSize)
{
    std::unordered_map<std::wstring, VertexShader*>::iterator iter = vertexShaders.find(file);
    if (iter != vertexShaders.end())
        return iter->second;

    // ������ �����ϴ�?�� ���� ������ �Է��� flag. bit OR �����ڸ� �̿��Ͽ� ������ bit ������ Ȯ���Ѵ�.
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // https://learn.microsoft.com/ko-kr/windows/win32/api/d3dcommon/nn-d3dcommon-id3d10blob
    ID3DBlob* vertexBlob;

    // Shader �������� �켱 ���ش�. �������� VS (hlsl ���� �� ���� �Ӽ� ����.)
    D3DCompileFromFile(
        file.c_str(), nullptr, nullptr,
        "VS", "vs_5_0", flags,
        0, &vertexBlob, nullptr
    );

    ID3D11VertexShader* shader;
    DEVICE->CreateVertexShader(
        vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
        nullptr, &shader
    );

    
    ID3D11InputLayout* inputLayout;
    DEVICE->CreateInputLayout(
        layoutDesc, layoutSize,
        vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
        &inputLayout
    );

    vertexBlob->Release();

    VertexShader* newVertexShader = new VertexShader(inputLayout, shader);
    vertexShaders.insert({ file, newVertexShader });

    return newVertexShader;
}

void VertexShader::Set()
{
    DC->IASetInputLayout(inputLayout);
    DC->VSSetShader(shader, nullptr, 0);
}

void VertexShader::Destroy()
{
    std::unordered_map<std::wstring, VertexShader*>::iterator iter;

    for (iter = vertexShaders.begin(); iter != vertexShaders.end(); iter++)
    {
        delete iter->second;
    }
    vertexShaders.clear();
}
