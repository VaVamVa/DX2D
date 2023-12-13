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
    // 창모드 여부 (false면 전체화면)
    swapChainDesc.Windowed = true;

    swapChainDesc.SwapEffect;
    swapChainDesc.Flags;

    D3D11CreateDeviceAndSwapChain(
        // 게임 중 창 관리용. 
        nullptr,
        // 이용할 드라이버
        D3D_DRIVER_TYPE_HARDWARE,
        // 이용할 모듈
        0,
        // 디버깅
        D3D11_CREATE_DEVICE_DEBUG,
        // featureLevel 안쓸거니까
        nullptr, 0,
        // SDK 버전
        D3D11_SDK_VERSION,
        // double ptr 형태로 변수를 넘겨 인터페이스들을 할당해 준다.
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
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };  // (임의값) window tutorial 기준 색.
    deviceContext->ClearRenderTargetView(rtv, clearColor);  // 한번 클리어
}

void Device::Present()
{
    swapChain->Present(0, 0);
}
