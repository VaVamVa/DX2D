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
    Plane* plane;

    wstring path = L"Textures/BeatShooter/";
    Transform* bgLight;

    Quad* bg2;
    Texture* bgLightTexture;
    ValueBuffer* valueBuffer;
};