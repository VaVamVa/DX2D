#include "Framework.h"

Timer::Timer()
{
    //1�ʵ��� CPU�������� ��ȯ�ϴ� �Լ�
    QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);

    //���� CPU�������� ��ȯ�ϴ� �Լ�
    QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

    timeScale = 1.0f / (float)periodFrequency;
}

void Timer::Update()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
    elapsedTime = (float)(curTime - lastTime) * timeScale;

    lastTime = curTime;

    frameCount++;
    oneSecCount += elapsedTime;

    if (oneSecCount >= 1.0f)
    {
        frameRate = frameCount;
        frameCount = 0;
        oneSecCount = 0.0f;
    }
}

void Timer::Render(HDC hdc)
{
    wstring str = L"FPS : " + to_wstring(frameRate);
    TextOut(hdc, 0, 0, str.c_str(), str.length());
    //str = L"Delta : " + to_wstring(elapsedTime);
    //TextOut(hdc, 0, 20, str.c_str(), str.length());
}