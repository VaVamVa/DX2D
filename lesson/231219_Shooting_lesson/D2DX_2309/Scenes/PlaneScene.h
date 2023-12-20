#pragma once

#include "Objects/ShootingGame/Plane.h"

class PlaneScene : public Scene
{
public:
    PlaneScene();
    ~PlaneScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    void CreateBG();

private:
    wstring path = L"Textures/BeatShooter/";

    Transform* bgLight;
};