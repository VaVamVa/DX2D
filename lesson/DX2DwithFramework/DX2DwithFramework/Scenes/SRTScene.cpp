#include "Framework.h"
#include "SRTScene.h"

SRTScene::SRTScene()
{
	rect = new Rect({ 200, 200 });
	worldBuffer = new MatrixBuffer();

	matWorld._11 = 1;
	matWorld._22 = 1;
	matWorld._33 = 1;
	matWorld._44 = 1;

	/*
	* ��� ��
	m41, m42�� ���� x, y �� �������Բ� ��İ� ����� ���´�.
	
	m11, m22�� ���� �ʺ�� ���̰� ���ϰԲ� ��İ� ����� ���´�.

	x, y�� ����
	cos sin
	-sin cos
	�� ���� �ϰ� �Ǹ� ��� ȸ���� �ǰ�,
	2D������ z �� ȸ������ ȸ�� �����ϱ⿡
	m11 m12
	m21 m22
	�� ���� �����ϴ�.
	*/
	pos.x = CENTER_X;
	pos.y = CENTER_Y;
}

SRTScene::~SRTScene()
{
	delete rect;
	delete worldBuffer;
}

void SRTScene::Update()
{
	
	if (V_KEY->Press(VK_LEFT))
	{
		scale.x -= DELTA;
		//matWorld._11 -= DELTA;
	}
	if (V_KEY->Press(VK_RIGHT))
	{
		scale.x += DELTA;
		//matWorld._11 += DELTA;
	}
	if (V_KEY->Press(VK_UP))
	{
		scale.y += DELTA;
		//matWorld._22 -= DELTA;
	}
	if (V_KEY->Press(VK_DOWN))
	{
		scale.y -= DELTA;
		//matWorld._22 += DELTA;
	}

	if (V_KEY->Press('S'))
	{
		pos.y -= 100 * DELTA;
		//matWorld._42 -= 100 * DELTA;
	}
	if (V_KEY->Press('W'))
	{
		pos.y += 100 * DELTA;
		//matWorld._42 += 100 * DELTA;
	}
	if (V_KEY->Press('A'))
	{
		pos.x -= 100 * DELTA;
		//matWorld._41 -= 100 * DELTA;
	}
	if (V_KEY->Press('D'))
	{
		pos.x += 100 * DELTA;
		//matWorld._41 += 100 * DELTA;
	}

	if (V_KEY->Press('E'))
		angle -= 10.0f * DELTA;
	if (V_KEY->Press('Q'))
		angle += 10.0f * DELTA;

	//matWorld._11 = cos(angle);
	//matWorld._12 = sin(angle);
	//matWorld._21 = -sin(angle);
	//matWorld._22 = cos(angle);

	//world = DirectX::XMLoadFloat4x4(&matWorld);
	Matrix S, R, T; // scale, rotation, translation
	S = DirectX::XMMatrixScaling(scale.x, scale.y, 1);
	R = DirectX::XMMatrixRotationZ(angle);
	T = DirectX::XMMatrixTranslation(pos.x, pos.y, 0);
	world = S * R * T;
}

void SRTScene::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	rect->Render();
}

void SRTScene::PostRender()
{
}

