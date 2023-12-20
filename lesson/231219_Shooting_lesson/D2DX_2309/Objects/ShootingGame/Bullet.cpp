#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet() : Quad(L"Textures/BeatShooter/playerBullet2.png", 9)
{
    isActive = false;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    if (!isActive) return;

    localPosition += direction * speed * DELTA;
    localRotation.z = direction.Angle();

    if (localPosition.x > SCREEN_WIDTH || localPosition.x < 0.0f)
        isActive = false;

    if (localPosition.y > SCREEN_HEIGHT || localPosition.y < 0.0f)
        isActive = false;

    UpdateWorld();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
    isActive = true;
    localPosition = pos;
    this->direction = direction;
    this->direction.Normalize();
}
