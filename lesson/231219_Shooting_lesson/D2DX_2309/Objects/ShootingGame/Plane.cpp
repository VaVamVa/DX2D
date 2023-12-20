#include "Framework.h"
#include "BulletManager.h"
#include "Plane.h"

Plane::Plane() : Quad(L"Textures/BeatShooter/player.png", 10)
{    
    localPosition = { CENTER_X, CENTER_Y };

    BulletManager::Get();
}

Plane::~Plane()
{
    BulletManager::Delete();
}

void Plane::Update()
{
    Move();
    Rotate();
    Fire();

    UpdateWorld();
}

void Plane::Move()
{
    if (KEY->Press('W'))
        localPosition.y += speed * DELTA;
    if (KEY->Press('S'))
        localPosition.y -= speed * DELTA;
    if (KEY->Press('A'))
        localPosition.x -= speed * DELTA;
    if (KEY->Press('D'))
        localPosition.x += speed * DELTA;
}

void Plane::Rotate()
{
    direction = mousePos - localPosition;
   
    float angle = atan2(direction.y, direction.x);
    float degree = angle * 180 / XM_PI;

    localRotation.z = angle;

    if (KEY->Press(VK_UP))
        localRotation.z += DELTA;
}

void Plane::Fire()
{
    if (KEY->Down(VK_LBUTTON))
    {
        BulletManager::Get()->Fire(localPosition, direction);
    }
}
