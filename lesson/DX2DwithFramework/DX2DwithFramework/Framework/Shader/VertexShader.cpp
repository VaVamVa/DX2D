#include "framework.h"

VertexShader::VertexShader(std::wstring file)
{
    // 컴파일 가능하니?에 대한 정보를 입력할 flag. bit OR 연산자를 이용하여 일정한 bit 공간을 확보한다.
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // https://learn.microsoft.com/ko-kr/windows/win32/api/d3dcommon/nn-d3dcommon-id3d10blob
    ID3DBlob* vertexBlob;

    // Shader 컴파일을 우선 해준다. 진입점은 VS (hlsl 파일 참고.)
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
    * 물방울 6.1 p 210~213
    struct D3D11_INPUT_ELEMENT_DESC
    {
        LPCSTR SemanticName;
            셰이더에서 의미소(semantic) 이름으로, 뜻이 명확해야 하며 셰이더의 입력 서명과 대응되어야 한다.
            셰이더의 콜론 뒤에 오는 이름이 semantic name이며, 이와 inputLayout용 DESC의 SemanticName이 같아야 한다.

        UINT SemanticIndex;
            하나의 정점 구조체에 텍스처 좌표가 여러 개 존재하는 경우 각 텍스처 좌표를 분간하기 위한 색인(index)
            셰이더 코드에서 semantic name 바로 뒤에 숫자로 표현된다. (default 0)

        DXGI_FORMAT Format;
            inputLayout의 자료 형식 지정

        UINT InputSlot;
            자료가 할당될 정점 버퍼 슬롯의 색인. 16(0~15)개의 슬롯을 지원한다.

        UINT AlignedByteOffset;
            입력 슬롯이 배열로 쓰일 경우, 직전 성분의 크기만큼 byte를 측정하여 다음 성분의 시작점을 기입한다.

        D3D11_INPUT_CLASSIFICATION InputSlotClass;
            인스턴싱에 쓰이지만, 현재는 `D3D11_INPUT_PER_VERTEX_DATA` 만 지정한다.

        UINT InstanceDataStepRate;
            인스턴싱에 쓰이지만, 현재는 `0` 만 지정한다.
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
