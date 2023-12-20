#include "Framework.h"
#include "Bullet.h"


Bullet::Bullet() : Quad(L"Textures/BeatShooter/playerBullet2.png", 9)
{
    isActive = false;

    localScale *= 0.4f;
    OBJ->Add(this);

    collider = new CircleCollider(GetSize().x * 0.5f);
    collider->SetParent(this);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    if (!isActive) return;

    localPosition += direction * speed * DELTA;
    localRotation.z = direction.Angle();

    /*
    if (localPosition.x > SCREEN_WIDTH || localPosition.x < 0.0f)
        isActive = false;

    if (localPosition.y > SCREEN_HEIGHT || localPosition.y < 0.0f)
        isActive = false;
    */

    if ((localPosition - CENTER).Length() > MAP_RADIUS)
        isActive = false;


    UpdateWorld();

}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
    localPosition = pos;
    this->direction = direction;
    this->direction.Normalize();
    isActive = true;

    UpdateWorld();
}
