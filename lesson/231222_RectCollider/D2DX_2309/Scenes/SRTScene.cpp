#include "Framework.h"
#include "SRTScene.h"

SRTScene::SRTScene()
{
    rect = new Quad({ 200, 200 });

    worldBuffer = new MatrixBuffer();

    matWorld._11 = 1;
    matWorld._22 = 1;
    matWorld._33 = 1;
    matWorld._44 = 1;

    matWorld._41 = CENTER_X;
    matWorld._42 = CENTER_Y;
}

SRTScene::~SRTScene()
{
    delete rect;
}

void SRTScene::Update()
{
    if (KEY->Press('W'))
        pos.y += 100 * DELTA;
        //matWorld._42 += 100 * DELTA;
    if (KEY->Press('S'))
        pos.y -= 100 * DELTA;
        //matWorld._42 -= 100 * DELTA;
    if (KEY->Press('A'))
        pos.x -= 100 * DELTA;
        //matWorld._41 -= 100 * DELTA;
    if (KEY->Press('D'))
        pos.x += 100 * DELTA;
        //matWorld._41 += 100 * DELTA;

    if (KEY->Press('T'))
        scale.y += 10 * DELTA;
        //matWorld._22 += 10 * DELTA;
    if (KEY->Press('G'))
        scale.y -= 10 * DELTA;
        //matWorld._22 -= 10 * DELTA;
    if (KEY->Press('F'))
        scale.x -= 10 * DELTA;
        //matWorld._11 -= 10 * DELTA;
    if (KEY->Press('H'))
        scale.x += 10 * DELTA;

    if (KEY->Press(VK_UP))
        angle += DELTA;
    if (KEY->Press(VK_DOWN))
        angle -= DELTA;

    //matWorld._11 = cos(angle);
    //matWorld._12 = sin(angle);
    //matWorld._21 = -sin(angle);
    //matWorld._22 = cos(angle);

    //world = XMLoadFloat4x4(&matWorld);

    Matrix S, R, T;
    S = XMMatrixScaling(scale.x, scale.y, 1);
    R = XMMatrixRotationZ(angle);
    T = XMMatrixTranslation(pos.x, pos.y, 0);   

    world = S * R * T;
}

void SRTScene::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    rect->Render();
}

void SRTScene::PostRender()
{
}
