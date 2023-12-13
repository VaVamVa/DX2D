#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Cpp Library : namespace std
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

// DirectX11 Library
#include <d3d11.h>
#include <DirectXMath.h> // namespace DirectX
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

typedef DirectX::XMFLOAT2 Float2;
typedef DirectX::XMFLOAT3 Float3;
typedef DirectX::XMFLOAT4 Float4;
typedef DirectX::XMMATRIX Matrix;

// Framework Header


// Object Header


// Scene Header



extern HWND hWnd;