#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Cpp Library : namespace std
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <functional>
#include <random>
#include <fstream>
#include <sstream>


// DirectX11 Library
#include <d3d11.h>
#include <DirectXMath.h> // namespace DirectX
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectX Tex
#include "Libraries/DirectXTex/DirectXTex.h" // namespace DirectX
#pragma comment(lib, "Libraries/lib/DirectXTex.lib")

// Developer making

// macro
#include "Framework/Utility/macro.h"

// Framework Math
#include "Framework/Math/Vector2D.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/GameMath.h"

// Framework Uility
#include "Framework/Utility/Singleton.h"

#include "Framework/Utility/VirtualKeyboard.h"
#include "Framework/Utility/Random.h"
#include "Framework/Utility/GameTimer.h"
#include "Framework/Utility/Utility.h"

// Framework Render
#include "Framework/Render/Device.h"
#include "Framework/Render/Texture.h"

// Render Shader
#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

// Render Buffer
#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"

// Render View
#include "Framework/Environment/Environment.h"

// Collider
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/CircleCollider.h"

// Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"

// Scene Header
#include "Scenes/Scene.h"

#include "Manager/GameManager.h"


extern HWND hWnd;
extern Vector2D mousePos;