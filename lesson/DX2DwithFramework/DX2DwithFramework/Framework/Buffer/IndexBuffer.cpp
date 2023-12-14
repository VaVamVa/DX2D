#include "framework.h"

IndexBuffer::IndexBuffer(void* data, UINT count)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(UINT) * count;
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    // 인덱스 버퍼를 초기화할 자료를 담은 시스템 메모리 배열을 가리키는 포인터.
    initData.pSysMem = data;  // 첫 주소

    DEVICE->CreateBuffer(&bufferDesc, &initData, &buffer);
}

IndexBuffer::~IndexBuffer()
{
    buffer->Release();
}

void IndexBuffer::Set()
{
    DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
}
