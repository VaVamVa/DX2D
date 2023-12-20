#pragma once

#define SAFE_DELETE(ptr) { if (ptr != nullptr) delete ptr; ptr = nullptr; }

#define FOR_OBJ(Iters) for(auto& iter : Iters)
#define FOR_OBJ_P(Iters) for(auto*& ptrIter : Iters)

#define FOR(i, _min, _max) for(int i = _min; i < _max; i++)
#define FOR_R(i, _max, _min) for(int i = _max; i > _min; i--)

constexpr int WIN_START_X = 100;
constexpr int WIN_START_Y = 10;

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

constexpr int CENTER_X = SCREEN_WIDTH >> 1;
constexpr int CENTER_Y = SCREEN_HEIGHT >> 1;

constexpr float PI = 3.141592;

#define V_KEY VirtualKeyboard::Get()
#define DELTA GameTimer::Get()->GetElapsedTime()
#define RAND Random::Get()

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

typedef DirectX::XMFLOAT2 Float2;
typedef DirectX::XMFLOAT3 Float3;
typedef DirectX::XMFLOAT4 Float4;
typedef DirectX::XMMATRIX Matrix;