#include "Framework.h"
#include "Plane.h"
#include "BulletManager.h"


Plane::Plane()
	:Rect({ 200.0f, 200.0f })
{
	worldBuffer = new MatrixBuffer();

	world = DirectX::XMMatrixIdentity();

	pos.x = CENTER_X;
	pos.y = CENTER_Y;
}

Plane::~Plane()
{
	delete worldBuffer;
}

void Plane::Update()
{
	Rotation();
	Translation();
	Fire();

	Matrix R, T;
	//S = DirectX::XMMatrixScaling(1, 1, 1);
	R = DirectX::XMMatrixRotationZ(angle);
	T = DirectX::XMMatrixTranslation(pos.x, pos.y, 0);
	world = R * T;
}

void Plane::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	Rect::Render();
}

void Plane::Rotation()
{
	angle = atan2(mousePos.x - pos.x, mousePos.y - pos.y);
}

void Plane::Translation()
{
	if (V_KEY->Press('S'))
	{
		if (pos.y - size.y * 0.5f > 0)
			pos.y -= 100 * DELTA;
		
		//matWorld._42 -= 100 * DELTA;
	}
	if (V_KEY->Press('W'))
	{
		if (pos.y + size.y * 0.5f < SCREEN_HEIGHT)
			pos.y += 100 * DELTA;
		//matWorld._42 += 100 * DELTA;
	}
	if (V_KEY->Press('A'))
	{
		if (pos.x - size.x * 0.5f > 0)
			pos.x -= 100 * DELTA;
		//matWorld._41 -= 100 * DELTA;
	}
	if (V_KEY->Press('D'))
	{
		if (pos.x + size.x * 0.5f < SCREEN_WIDTH)
			pos.x += 100 * DELTA;
		//matWorld._41 += 100 * DELTA;
	}
}

void Plane::Fire()
{
	if (V_KEY->Down(VK_LBUTTON))
	{
		BulletManager::Get()->Fire(pos, angle - DirectX::XM_PIDIV2);
	}
}
