#include "Framework.h"
#include "Bullet.h"

#include "EnemyManager.h"

Bullet::Bullet() : Quad(L"Textures/BeatShooter/playerBullet2.png", 9)
{
    isActive = false;

    localScale *= 0.4f;
    OBJ->Add(this);

    collider = new CircleCollider(GetSize().x * 0.3f);
    collider->SetParent(this);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    if (!IsActive()) return;

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

    if (EnemyManager::Get()->IsCollision(collider))
    {
        isActive = false;
    }


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
