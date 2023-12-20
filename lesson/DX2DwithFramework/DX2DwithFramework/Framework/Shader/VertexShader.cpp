#include "framework.h"

VertexShader::VertexShader(std::wstring file)
{
    // 컴파일 가능하니?에 대한 정보를 입력할 flag. bit OR 연산자를 이용하여 일정한 bit 공간을 확보한다.
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // Shader 컴파일을 우선 해준다. 진입점은 4번째 매개변수 (hlsl 파일 및 파일 속성 참고.)
    D3DCompileFromFile(
        file.c_str(), nullptr, nullptr,
        "VS", "vs_5_0", flags, 0,
        &blob, nullptr
    );

    DEVICE->CreateVertexShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &shader);

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

    D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize = ARRAYSIZE(layoutDesc);

    DEVICE->CreateInputLayout(layoutDesc, layoutSize,
        blob->GetBufferPointer(), blob->GetBufferSize(),
        &inputLayout);
    */
    CreateInputLayout();
}

VertexShader::~VertexShader()
{
    shader->Release();
}

void VertexShader::CreateInputLayout()
{
    D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&reflection);

    D3D11_SHADER_DESC shaderDesc;
    reflection->GetDesc(&shaderDesc);

    std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
    inputLayouts.reserve(shaderDesc.InputParameters);

    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask < 2)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask < 4)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask < 8)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask < 16)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        std::string temp = paramDesc.SemanticName;

        if (temp == "POSITION")  // sementic 체크 하여 Shader에 넘어가는 값이 Float4로 넘어가게 바꿔줌.
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        int n = temp.find_first_of('_');
        temp = temp.substr(0, n);

        if (temp == "INSTANCE")  // 최적화 관련
        {
            elementDesc.InputSlot = 1;
            elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
            elementDesc.InstanceDataStepRate = 1;
        }

        inputLayouts.push_back(elementDesc);
    }

    DEVICE->CreateInputLayout(inputLayouts.data(), inputLayouts.size(),
        blob->GetBufferPointer(), blob->GetBufferSize(),
        &inputLayout);
}

void VertexShader::Set()
{
    DC->IASetInputLayout(inputLayout);
    DC->VSSetShader(shader, nullptr, 0);
}