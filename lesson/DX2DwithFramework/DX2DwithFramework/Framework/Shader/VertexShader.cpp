#include "framework.h"

VertexShader::VertexShader(std::wstring file)
{
    // ������ �����ϴ�?�� ���� ������ �Է��� flag. bit OR �����ڸ� �̿��Ͽ� ������ bit ������ Ȯ���Ѵ�.
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // Shader �������� �켱 ���ش�. �������� 4��° �Ű����� (hlsl ���� �� ���� �Ӽ� ����.)
    D3DCompileFromFile(
        file.c_str(), nullptr, nullptr,
        "VS", "vs_5_0", flags, 0,
        &blob, nullptr
    );

    DEVICE->CreateVertexShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &shader);

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

        if (temp == "POSITION")  // sementic üũ �Ͽ� Shader�� �Ѿ�� ���� Float4�� �Ѿ�� �ٲ���.
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        int n = temp.find_first_of('_');
        temp = temp.substr(0, n);

        if (temp == "INSTANCE")  // ����ȭ ����
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