#pragma once

class Timer : public Singleton<Timer>
{
private:
    const float EPSILON = 0.01f;

private:
    friend class Singleton;

    Timer();
    ~Timer() = default;

public:
    void Update();
    void Render(HDC hdc);

    void SetDeltaScale(float value) { deltaScale = value; }

    float GetElapsedTime() { return elapsedTime > EPSILON ? EPSILON : elapsedTime * deltaScale; }

private:
    float timeScale = 0.0f;
    float elapsedTime = 0.0f;
    float oneSecCount = 0.0f;
    float deltaScale = 1.0f;

    __int64 curTime = 0;
    __int64 lastTime = 0;
    __int64 periodFrequency = 0;

    int frameRate = 0;
    int frameCount = 0;
    int lockFPS = 0;
};