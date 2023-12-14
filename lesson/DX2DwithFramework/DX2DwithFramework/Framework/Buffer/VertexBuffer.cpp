#include "framework.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count)
	:stride(stride)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = stride * count;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    // 정점 버퍼를 초기화할 자료를 담은 시스템 메모리 배열을 가리키는 포인터.
    initData.pSysMem = data;  // 첫 주소

    DEVICE->CreateBuffer(&bufferDesc, &initData, &buffer);
}

VertexBuffer::~VertexBuffer()
{
    buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
{
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

    DC->IASetPrimitiveTopology(type);
}
