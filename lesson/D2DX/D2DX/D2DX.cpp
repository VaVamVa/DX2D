#include "framework.h"
#include "D2DX.h"

#define MAX_LOADSTRING 100

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

void Init();
void Render();
void Release();

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
            Render();
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
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    // RAM에 할당되는(CPU) 정보들
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
}

void Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };  // (임의값) window tutorial 기준 색.
    deviceContext->ClearRenderTargetView(rtv, clearColor);  // 한번 클리어

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
