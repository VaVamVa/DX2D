#pragma once

class PlaneScene : public Scene
{
private:
    const wstring PATH = L"Textures/BeatShooter/";

public:
    PlaneScene();
    ~PlaneScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    void CreateBG();

private:
    Transform* bgLight;

    class Plane* plane;
};