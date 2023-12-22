#include "Framework.h"
#include "BulletManager.h"
#include "Plane.h"

Plane::Plane() : Quad(L"Textures/BeatShooter/player.png", 10)
{    
    localPosition = { CENTER_X, CENTER_Y };
    localScale *= 0.4f;

    BulletManager::Get();

    collider = new CircleCollider(GetSize().x * 0.5f);
    collider->SetParent(this);
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
        //velocity.y = 1;
        velocity = GetRight();  // 이미지가 오른쪽을 보기에..
        isMove = true;
    }
    if (KEY->Press('S'))
    {
        //velocity.y = -1;
        velocity = GetRight() * -1.0f;
        isMove = true;
    }
    /*if (KEY->Press('A'))
    {
        velocity.x = -1;
        isMove = true;
    }
    if (KEY->Press('D'))
    {
        velocity.x = 1;
        isMove = true;
    }        */

    if (!isMove)
        velocity = { 0, 0 };
    else
        velocity.Normalize();

    float distance = Distance(localPosition, CENTER);

    if (distance > MAP_RADIUS)
    {
        Vector2 normal = (CENTER - localPosition).GetNormalized();
        //velocity = velocity - normal * (Dot(velocity, normal));

        Translate(normal * MAP_PUSH_SPEED * DELTA);
    }

    Translate(velocity * speed * DELTA);
}

void Plane::Rotate()
{
    /*direction = mousePos - localPosition;
   
    float angle = atan2(direction.y, direction.x);
    float degree = angle * 180 / XM_PI;

    localRotation.z = angle;*/

    if (KEY->Press('A'))
        localRotation.z += DELTA;
    if (KEY->Press('D'))
        localRotation.z -= DELTA;
}

void Plane::Fire()
{
    if (KEY->Down(VK_LBUTTON))
    {
        BulletManager::Get()->Fire(localPosition, direction);
    }
}
