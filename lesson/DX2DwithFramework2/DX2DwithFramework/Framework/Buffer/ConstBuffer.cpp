#include "framework.h"
#include "ConstBuffer.h"

ConstBuffer::ConstBuffer(void* data, UINT stride)
	:data(data), stride(stride)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(UINT) * stride;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    DEVICE->CreateBuffer(&bufferDesc, nullptr, &buffer);
}

ConstBuffer::~ConstBuffer()
{
    buffer->Release();
}

void ConstBuffer::SetVS(UINT slot)
{
    // RAM data(data)를 GPU(VRAM)를 다루는 buffer에 넣는다.
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->VSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetPS(UINT slot)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->PSSetConstantBuffers(slot, 1, &buffer);
}
