#pragma once

class SRTScene : public Scene
{
public:
    SRTScene();
    ~SRTScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    Quad* rect;

    MatrixBuffer* worldBuffer;

    Matrix world;
    XMFLOAT4X4 matWorld;

    Float2 pos = {};
    Float2 scale = { 1, 1 };
    float angle = 0;
};