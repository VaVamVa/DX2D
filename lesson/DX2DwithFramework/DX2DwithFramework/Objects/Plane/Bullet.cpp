#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
	pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

	float size = 30.0f;

	vertices.emplace_back(0, size, 1, 0, 0);
	vertices.emplace_back(size, 0, 1, 1, 1);
	vertices.emplace_back(-size, 0, 1, 1, 1);
	vertices.emplace_back(0, -size, 1, 1, 1);
	vertices.emplace_back(size, -2.0f * size, 0, 1, 0);
	vertices.emplace_back(-size, -2.0f * size, 0, 1, 0);

	indices = { 0, 1, 2, 1, 3, 2, 1, 4, 3, 2, 3, 5 };

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), indices.size());

	worldBuffer = new MatrixBuffer();
	world = DirectX::XMMatrixIdentity();
}

Bullet::~Bullet()
{
	delete worldBuffer;

	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete indexBuffer;

	indices.clear();
}

void Bullet::Update()
{
	if (!active)
		return;

	Translation();

	Matrix R, T;
	R = DirectX::XMMatrixRotationZ(angle - DirectX::XM_PIDIV2);
	T = DirectX::XMMatrixTranslation(pos.x, pos.y, 0);
	world = R * T;

	Destroy();
}

void Bullet::Render()
{
	if (!active)
		return;

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	
	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Bullet::Fire(Float2 pos, float direction)
{
	this->pos = pos;
	angle = direction;
	active = true;
}

void Bullet::Translation()
{
	pos.x += cos(angle) * SPEED * DELTA;
	pos.y += sin(angle) * SPEED * DELTA;
}

void Bullet::Destroy()
{
	if (pos.x < 0 || pos.x > SCREEN_WIDTH
		|| pos.y < 0 || pos.y > SCREEN_HEIGHT)
		active = false;
}
