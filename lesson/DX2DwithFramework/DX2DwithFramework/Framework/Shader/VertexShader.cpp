#include "framework.h"

VertexShader::VertexShader(std::wstring file)
{
    // ������ �����ϴ�?�� ���� ������ �Է��� flag. bit OR �����ڸ� �̿��Ͽ� ������ bit ������ Ȯ���Ѵ�.
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // https://learn.microsoft.com/ko-kr/windows/win32/api/d3dcommon/nn-d3dcommon-id3d10blob
    ID3DBlob* vertexBlob;

    // Shader �������� �켱 ���ش�. �������� VS (hlsl ���� ����.)
    D3DCompileFromFile(
        file.c_str(), nullptr, nullptr,
        "VS", "vs_5_0", flags,
        0, &vertexBlob, nullptr
    );

    DEVICE->CreateVertexShader(
        vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
        nullptr, &shader
    );


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
