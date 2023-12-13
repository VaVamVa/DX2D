#include "framework.h"
#include "D2DX.h"

#define MAX_LOADSTRING 100

struct Vertex // 정점 : 3차원 공간에서의 한 점
{
    DirectX::XMFLOAT3 pos = {};  // x, y, z
    DirectX::XMFLOAT4 color = {};

    Vertex(float x, float y)
        :pos(x, y, 0.0f) {}

    Vertex(float x, float y, float r, float g, float b)
        :pos(x, y, 0.0f), color(r, g, b, 1) {}
};

std::vector<Vertex> vertices;

HINSTANCE hInst;
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

//CPU - 직렬 처리 (복잡한 연산을 빠르게 처리_resource 및 객체 생성)
ID3D11Device* device;

//GPU - 병렬 처리 (다수의 연산을 한번에 처리_출력)
ID3D11DeviceContext* deviceContext;

/*
* Double Buffer
Front Buffer와 Back Buffer 두개의 버퍼를 두어,
프레임 마다 앞과 뒤의 버퍼들이 각각 출력물을 준비하고,
번갈아 가며 화면에 출력한다.
*/
IDXGISwapChain* swapChain;

/*
V_RAM과 RAM을 이어주는 매개체.
보통 V_RAM은 Render의 역할만 하기 때문에 RAM에서 V_RAM으로 정보를 보내는데 이용된다.
*/
ID3D11RenderTargetView* rtv;

///////// shader 적용부
ID3D11VertexShader* vertexShader;
ID3D11PixelShader* pixelShader;
ID3D11InputLayout* inputLayout;
ID3D11Buffer* vertexBuffer;

void Init();
void Render();
void Release();

// 임의 update. 추후 프레임워크 만들 시 지워야함.
int vertexNumber = 3;
float radius = 0.5f;
D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
void Update();

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_D2DX, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D2DX));

    MSG msg = {};

    Init();

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            Update();
            Render();
            V_KEY->Update();
        }
    }

    Release();

    return (int) msg.wParam;
}


void Init()
{
    UINT width = SCREEN_WIDTH;
    UINT height = SCREEN_HEIGHT;

    // DESC_description : 구체적인 내용을 담고 있는 구조체
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};  // 구조체 내부 자료들을 0으로 초기화

    // BufferDesc : Front, Back buffer 특성
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    // 모니터 주사율 = Numerator / Denominator _ 모니터 깜빡임 정도
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    // 색깔 표현 UNORM -> unsigned(부호가 없는) Normalization(정규화_0~1 * 4 내에서 표현)
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Alpha값이 추가되었기에 PNG 파일 쓰자.

    // SampleDesc : 표본화 - antialincing(계단화) 방지.
    // DX에서는 다중 표본화 이용. 구역을 나누어 연산하여 통합
    // Count = 1, Quality = 0  - 안쓰겠다.
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    // RENDER_TARGET 후면버퍼, OUTPUT 출력 = 후면버퍼 출력용
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // 하나만 쓸거다. (Front 출력용, Back 저장용)
    swapChainDesc.BufferCount = 1;

    // 출력에 이용할 버퍼(윈도우 창)
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

    // (CPU에 의해) RAM에 할당되는 정보들
    ID3D11Texture2D* backBuffer;

    /*
    어떤 행동이 들어올지 모르기에 void**로 넘기지만,
    두번째 매개변수에 자료형(interface id)을 같이 넘겨준다.
    */
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
    backBuffer->Release();

    // rtv에 있는 정보로 출력해라. deviceContext => GPU => 출력용
    deviceContext->OMSetRenderTargets(1, &rtv, nullptr);


    //// shader 적용부
    D3D11_VIEWPORT viewPort = {};
    // 정규화 된 3차원 공간을 viewPort의 크기 만큼 2차원으로 변환하여 화면에 출력한다.
    viewPort.Width = width;
    viewPort.Height = height;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;

    deviceContext->RSSetViewports(1, &viewPort);

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* vertexBlob;
    // 4번째 매개변수 : 진입점
    D3DCompileFromFile(L"Shaders/Tutorial.hlsl", nullptr, nullptr,
        "VS", "vs_5_0", flags,
        0, &vertexBlob, nullptr
    );

    // vertex shader용 buffer 생성
    device->CreateVertexShader(
        vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
        nullptr, &vertexShader
    );

    // sementic number = default 0. 아니면 뒤에 숫자 적어넣음
    // 쉐이더가 가지고있는 속성 수 대로 배열 원소 생성
    D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,  // 앞에 당겨진 바이트 수 입력
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize = ARRAYSIZE(layoutDesc);

    device->CreateInputLayout(layoutDesc, layoutSize,
        vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
        &inputLayout
    );

    ID3DBlob* pixelBlob;
    // 4번째 매개변수 : 진입점
    D3DCompileFromFile(L"Shaders/Tutorial.hlsl", nullptr, nullptr,
        "PS", "ps_5_0",
        flags, 0, &pixelBlob, nullptr
    );

    device->CreatePixelShader(
        pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(),
        nullptr, &pixelShader
    );

    float aVertexAngle = 2.0f * PI / vertexNumber;
    FOR(i, 0, vertexNumber)
    {
        vertices.emplace_back(0, 0, 1, 1, 1);
        vertices.emplace_back(radius * sin(aVertexAngle * i), radius * cos(aVertexAngle * i), 0, 1, 0);
        vertices.emplace_back(radius * sin(aVertexAngle * (i + 1)), radius * cos(aVertexAngle * (i + 1)), 0, 0, 1);
    }

    // buffer : VRAM에 할당되는 메모리
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices.data();  // 첫 주소

    device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}

/*
* Rendering Pipeline
GPU가 화면에 출력하는 과정
1. Input Assembler(IA) : CPU에 있는 정보를 가져오는 단계
2. Vertex Shader : 정점 쉐이더
(3.) Hull Shader, tS, Depth Stencil, Geometry Shader
4. Rasterizer State : NDC 좌표를 출력하기 위해 viewPort 변환을 해주는 과정.
    - 또한 폴리곤(STRIP)에서 color를 선형보간으로 채워준다.
5. Pixel Shader
6. OM : Output Merge

Shader : GPU 언어. - 우리가 짜야하는 스크립트
    - hlsl(hi-level shader language)
    - 확장-확장 관리-HLSL Tool for Visual Studio 검색/설치
        - 만약 자동으로 작업관리자 Manage bar 보일경우 해당 버튼 클릭 후 추가설치 X
    - 프로젝트 속성-HLSL 컴파일러-진입점 이름 : VS, 셰이더 모델 ShaderModel 5.0 (DX11 용)
*/
void Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };  // (임의값) window tutorial 기준 색.
    deviceContext->ClearRenderTargetView(rtv, clearColor);  // 한번 클리어

    UINT stride = sizeof(Vertex);  // 정점 하나의 크기
    UINT offset = 0;

    deviceContext->IASetInputLayout(inputLayout);

    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    //변경 전 값 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
    deviceContext->IASetPrimitiveTopology(topology);

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);

    deviceContext->Draw(vertices.size(), 0);  // 렌더링 파이프라인 실행

    // backBuffer에 정보 담기
    swapChain->Present(0, 0);
}

void Release()
{
    device->Release();
    deviceContext->Release();

    swapChain->Release();
    rtv->Release();
}

void Update()
{
    bool controlFlag = true;
    if (V_KEY->Down(VK_UP))
    {
        vertexNumber++;
        vertices.clear();
        controlFlag = false;
    }
    if (vertexNumber > 3 && V_KEY->Down(VK_DOWN))
    {
        vertexNumber--;
        vertices.clear();
        controlFlag = false;
    }

    if (radius < 1.0f && V_KEY->Down(VK_RIGHT))
    {
        radius += 0.1f;
        vertices.clear();
        controlFlag = false;
    }
    if (radius > 0.1f && V_KEY->Down(VK_LEFT))
    {
        radius -= 0.1f;
        vertices.clear();
        controlFlag = false;
    }

    if (V_KEY->Down(VK_SPACE))
    {
        vertices.clear();
        controlFlag = false;
        topology = topology == D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP ? D3D11_PRIMITIVE_TOPOLOGY_LINELIST : D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    }

    if (controlFlag)
        return;

    // Polygon(strip) : 정점 3개로 이루어진 삼각형
    // 정점 순서에 따라 시계방향이 앞면을 의미하며, 앞면만 출력.
    // 시계 반대방향으로 돌리면, 뒷면(출력되지 않는 면)이 화면을 바라보게 됨.

    /* tri_list to rect
    vertices.emplace_back(+0.5f, +0.5f);
    vertices.emplace_back(+0.5f, -0.5f);
    vertices.emplace_back(-0.5f, -0.5f);

    vertices.emplace_back(-0.5f, -0.5f);
    vertices.emplace_back(-0.5f, +0.5f);
    vertices.emplace_back(+0.5f, +0.5f);
    */

    /* tri_strip to rect
    vertices.emplace_back(+0.5f, +0.5f, 1, 0, 0);  // 첫번째 strip은 시계 방향으로
    vertices.emplace_back(+0.5f, -0.5f, 1, 1, 1);  // 두번째 strip 부터 시계 반대로.
    vertices.emplace_back(-0.5f, +0.5f, 0, 0, 1);
    vertices.emplace_back(-0.5f, -0.5f, 0, 1, 0);
    */

    /* tri_strip to penta
    vertices.emplace_back(0.0f, 0.5f, 0, 1, 0);
    vertices.emplace_back(0.5f, 0.0f, 0, 1, 0);
    vertices.emplace_back(-0.5f, 0.0f, 0, 1, 0);
    vertices.emplace_back(0.25f, -0.5f, 0, 1, 0);
    vertices.emplace_back(-0.25f, -0.5f, 0, 1, 0);
    */

    // Polygon
    float aVertexRadian = 2.0f * PI / vertexNumber;
    switch (topology)
    {
    case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
    {
        if (vertexNumber % 2)
        {
            FOR(i, 1, vertexNumber + 1)
            {
                vertices.emplace_back(0, 0, 1, 1, 1);
                vertices.emplace_back(radius * sin(aVertexRadian * i), radius * cos(aVertexRadian * i), 1, 0, 0);
                vertices.emplace_back(radius * sin(aVertexRadian * (i + 1)), radius * cos(aVertexRadian * (i + 1)), 0, 0, 1);
            }
        }
        else
        {
            FOR(i, 1, vertexNumber + 1)
            {
                vertices.emplace_back(0, 0, 1, 1, 1);
                vertices.emplace_back(radius * cos(aVertexRadian * i), radius * sin(aVertexRadian * i), 1, 0, 0);
                vertices.emplace_back(radius * cos(aVertexRadian * (i + 1)), radius * sin(aVertexRadian * (i + 1)), 0, 0, 1);
            }
        }
        break;
    }
    case D3D11_PRIMITIVE_TOPOLOGY_LINELIST:
    {
        FOR(i, 0, vertexNumber)
        {
            vertices.emplace_back(radius * sin(aVertexRadian * i), radius * cos(aVertexRadian * i), 1, 0, 0);
            vertices.emplace_back(radius * sin(aVertexRadian * (i + 1)), radius * cos(aVertexRadian * (i + 1)), 0, 0, 1);
        }
        break;
    }
    }

    // buffer : VRAM에 할당되는 메모리
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices.data();  // 첫 주소

    device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D2DX));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_D2DX);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   RECT winRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

   AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, false);

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      WIN_START_X, WIN_START_Y,
       winRect.right - winRect.left, winRect.bottom - winRect.top, 
       nullptr, nullptr, hInstance, nullptr);

   SetMenu(hWnd, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hWnd, &ps);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
