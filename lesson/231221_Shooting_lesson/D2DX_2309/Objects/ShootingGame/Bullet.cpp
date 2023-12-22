#include "Framework.h"
#include "Bullet.h"

#include "EnemyManager.h"

Bullet::Bullet() : Quad(L"Textures/BeatShooter/playerBullet2.png", 9)
{
    localScale *= 0.4f;

    isActive = false;

    collider = new CircleCollider(GetSize().x * 0.3f);
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

    float distance = Distance(localPosition, CENTER);

    if (distance > MAP_RADIUS)
        isActive = false;

    if (EnemyManager::Get()->Collision(collider))
    {
        isActive = false;
    }

    UpdateWorld();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
    isActive = true;
    localPosition = pos;
    this->direction = direction;
    this->direction.Normalize();

    UpdateWorld();
}
