#include "Framework.h"
#include "PlaneL.h"

#include "BulletManager.h"

Plane::Plane()
	:Quad(L"Textures/BeatShooter/player.png")
{
	DirectX::ScratchImage image;
	localPosition.x = CENTER_X;
	localPosition.y = CENTER_Y;

	active = true;
}

Plane::~Plane()
{
}

void Plane::Update()
{
	Move();
	Aim();

	Fire();

	UpdateWorld();
}

void Plane::Render()
{
	Quad::Render();
}

void Plane::Move()
{
	if (V_KEY->Press('S'))
	{
		localPosition.y -= speed * DELTA;
	}
	if (V_KEY->Press('W'))
	{
		localPosition.y += speed * DELTA;
	}
	if (V_KEY->Press('A'))
	{
		localPosition.x -= speed * DELTA;
	}
	if (V_KEY->Press('D'))
	{
		localPosition.x += speed * DELTA;
	}
}

void Plane::Aim()
{
	direction = mousePos - localPosition;

	localRotation.z = atan2(direction.y, direction.x);
}

void Plane::Fire()
{
	if (V_KEY->Down(VK_LBUTTON))
		BulletManager::Get()->Fire(localPosition, direction);
}
