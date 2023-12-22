#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_START_X 50
#define WIN_START_Y 50

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define CENTER_X (SCREEN_WIDTH * 0.5f)
#define CENTER_Y (SCREEN_HEIGHT * 0.5f)

#define CENTER Vector2(CENTER_X, CENTER_Y)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define KEY Keyboard::Get()
#define DELTA Timer::Get()->GetElapsedTime()
#define OBJ ObjectManager::Get()

#define FOR(n) for(int i = 0 ; i < n ; i++)

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <functional>
#include <algorithm>
#include <random>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include "Libraries/DirectXTex/DirectXTex.h"
#pragma comment(lib, "Libraries/Lib/DirectXTex.lib")

//ImGui
#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_dx11.h"
#include "Libraries/ImGui/imgui_impl_win32.h"
#pragma comment(lib, "Libraries/Lib/ImGui.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT2 Float2;
typedef XMFLOAT3 Float3;
typedef XMFLOAT4 Float4;
typedef XMMATRIX Matrix;

//Framework Header
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Keyboard.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Random.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"
#include "Framework/Math/Transform.h"

using namespace GameMath;

#include "Framework/Render/Device.h"
#include "Framework/Render/Texture.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Collider/Collider.h"
#include "Framework/Collider/CircleCollider.h"
#include "Framework/Collider/RectCollider.h"

#include "Framework/Environment/Environment.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/ObjectManager.h"
#include "Objects/Basic/Quad.h"

//Scene Header
#include "Scenes/Scene.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;