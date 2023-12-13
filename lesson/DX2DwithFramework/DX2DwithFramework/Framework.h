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
#include <random>

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
#include "Framework/Utility/Singleton.h"

#include "Framework/Render/Device.h"

#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Utility/VirtualKeyboard.h"
#include "Framework/Utility/Random.h"
#include "Framework/Utility/GameTimer.h"
#include "Framework/Utility/Utility.h"

#include "Framework/Utility/macro.h"

// Object Header


// Scene Header
#include "Scenes/Scene.h"

#include "Manager/GameManager.h"


extern HWND hWnd;