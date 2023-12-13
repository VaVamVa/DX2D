#include "framework.h"

Device::Device()
{
    UINT width = SCREEN_WIDTH;
    UINT height = SCREEN_HEIGHT;

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;

    swapChainDesc.OutputWindow = hWnd;
    // â��� ���� (false�� ��üȭ��)
    swapChainDesc.Windowed = true;

    swapChainDesc.SwapEffect;
    swapChainDesc.Flags;

    D3D11CreateDeviceAndSwapChain(
        // ���� �� â ������. 
        nullptr,
        // �̿��� ����̹�
        D3D_DRIVER_TYPE_HARDWARE,
        // �̿��� ���
        0,
        // �����
        D3D11_CREATE_DEVICE_DEBUG,
        // featureLevel �Ⱦ��Ŵϱ�
        nullptr, 0,
        // SDK ����
        D3D11_SDK_VERSION,
        // double ptr ���·� ������ �Ѱ� �������̽����� �Ҵ��� �ش�.
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    ID3D11Texture2D* backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
}

Device::~Device()
{
    device->Release();
    deviceContext->Release();

    swapChain->Release();
    rtv->Release();
}

void Device::Clear()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };  // (���ǰ�) window tutorial ���� ��.
    deviceContext->ClearRenderTargetView(rtv, clearColor);  // �ѹ� Ŭ����
}

void Device::Present()
{
    swapChain->Present(0, 0);
}
