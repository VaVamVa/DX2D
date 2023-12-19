#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet()
	:Quad(L"Textures/BeatShooter/playerBullet2.png")
{
}

void Bullet::Update()
{
	if (!active) return;

	localPosition += direction * speed * DELTA;
	localRotation.z = direction.Angle();

	if (localPosition.x > SCREEN_WIDTH || localPosition.x < 0.0f)
		active = false;

	if (localPosition.y > SCREEN_HEIGHT || localPosition.y < 0.0f)
		active = false;

	UpdateWorld();
}

void Bullet::Render()
{
	Quad::Render();
}

void Bullet::Fire(Vector2D pos, Vector2D direction)
{
	active = true;

	localPosition = pos;
	this->direction = direction.GetNormalized();
}


