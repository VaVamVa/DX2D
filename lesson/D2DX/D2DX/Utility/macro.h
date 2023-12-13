#pragma once

#define SAFE_DELETE(ptr) { if (ptr != nullptr) delete ptr; ptr = nullptr; }

#define FOR_OBJ(Iters) for(auto& iter : Iters)
#define FOR_OBJ_P(Iters) for(auto*& iter : Iters)

#define FOR(i, _min, _max) for(int i = _min; i < _max; i++)
#define FOR_R(i, _max, _min) for(int i = _max; i > _min; i--)

constexpr int WIN_START_X = 100;
constexpr int WIN_START_Y = 10;

constexpr int SCREEN_WIDTH = 900;
constexpr int SCREEN_HEIGHT = 900;

constexpr float PI = 3.141592;

#define V_KEY VirtualKeyboard::Get()