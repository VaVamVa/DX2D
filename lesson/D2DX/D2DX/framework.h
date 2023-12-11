#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/*
- DirectX 란.
Microsoft 에서 만든 게임 개발을 위해 만든 SDK(Software Development)
운영체제를 통해야 하는 window 기반 게임은 DOS 기반 게임에 비해 느렸다.
이를 해결하기 위해, window에서 프로그래머의 의도 하에
직접 접근(Direct Exess)하여 게임 속도를 빠르게 하기 위한 프로그램.

DirectX 9 부터는 3D 라이브러리가 모두 추가되며,
직접 접근의 의미보다는 3D 라이브러리의 의도가 더욱 강해졌다.

버전이 증가할 수록 최적화(프로그래머가 하드웨어에 직접 접근하는 부분을 증가시킴)가
더욱 증가하였다.

(핵심) Direct X11 을 배우며 "엔진이 어떤식으로 만들어지는 가"에 대한
개념을 배우게 된다.
*/
// DirectX11 라이브러리
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "Utility/macro.h"


extern ID3D11Device* device;
extern ID3D11DeviceContext* deviceContext;

extern IDXGISwapChain* swapChain;
extern ID3D11RenderTargetView* rtv;