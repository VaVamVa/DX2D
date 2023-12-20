#include "Framework.h"
#include "BulletManager.h"
#include "Plane.h"

Plane::Plane() : Quad(L"Textures/BeatShooter/player.png", 10)
{    
    localPosition = { CENTER_X, CENTER_Y };
    localScale = { 0.4f, 0.4f };

    BulletManager::Get();

    collider = new CircleCollider(GetSize().x * 0.5f);
    collider->SetParent(this);  // scale, pos ´Ù »ó¼ÓµÊ
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
    bool isMove = false;

    if (KEY->Press('W'))
    {
        velocity.y = speed;
        isMove = true;
    }
    if (KEY->Press('S'))
    {
        velocity.y = -speed;
        isMove = true;
    }
    if (KEY->Press('A'))
    {
        velocity.x = -speed;
        isMove = true;
    }
    if (KEY->Press('D'))
    {
        velocity.x = speed;
        isMove = true;
    }

    if (!isMove)
        velocity = Vector2();

    float distance = Distance(localPosition, CENTER);

    /*
    // sliding vector : https://toymaker.tistory.com/entry/%EB%AF%B8%EB%81%84%EB%9F%AC%EC%A7%90-%EB%B2%A1%ED%84%B0-Sliding-Vector
    if (distance >= MAP_RADIUS)
    {
        // sliding vector
        velocity = velocity - normalVector * Dot(velocity, normalVector);

        Translate(normalVector * MAP_PUSH_SPEED * DELTA);
    }
    */
    if (distance >= MAP_RADIUS)
    {
        Vector2 normalVector = (CENTER - localPosition).GetNormalized();
        Translate(normalVector * MAP_PUSH_SPEED * DELTA);
    }

    Translate(velocity * DELTA);
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
