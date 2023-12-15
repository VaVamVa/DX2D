#include "Framework.h"
#include "PlaneL.h"

#include "BulletManager.h"

PlaneL::PlaneL()
	:Quad(L"Textures/BeatShooter/player.png")
{
	DirectX::ScratchImage image;
	localPosition.x = CENTER_X;
	localPosition.y = CENTER_Y;

	active = true;
}

PlaneL::~PlaneL()
{
	BulletManager::Delete();
}

void PlaneL::Update()
{
	Move();
	Rotate();

	Fire();

	UpdateWorld();
}

void PlaneL::Render()
{
	Quad::Render();
}

void PlaneL::Move()
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

void PlaneL::Rotate()
{
	direction = mousePos - localPosition;

	localRotation.z = atan2(direction.y, direction.x);
}

void PlaneL::Fire()
{
	if (V_KEY->Down(VK_LBUTTON))
		BulletManager::Get()->Fire(localPosition, direction);
}
