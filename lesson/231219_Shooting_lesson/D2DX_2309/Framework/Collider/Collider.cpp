#include "Framework.h"

vector<Collider*> Collider::colliders;

Collider::Collider()
{
	vertexShader = Shader::AddVS(L"VertexPos.hlsl");
	pixelShader = Shader::AddPS(L"PixelPos.hlsl");

	worldBuffer = new MatrixBuffer();

	colorBuffer = new ColorBuffer();
	colorBuffer->Set(0, 1, 0);

	colliders.push_back(this);
}

Collider::~Collider()
{
	delete worldBuffer;
	delete colorBuffer;
}

void Collider::Render()
{
	if (!isActive) return;

	colorBuffer->SetPS(0);

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	vertexShader->Set();
	pixelShader->Set();

	DC->Draw(vertices.size(), 0);
}

bool Collider::IsCollision(Collider* collider)
{
	return false;
}

void Collider::TotalUpdate()
{
	for (Collider* collider : colliders)
		collider->UpdateWorld();
}

void Collider::TotalRender()
{
	for (Collider* collider : colliders)
		collider->Render();
}

void Collider::Delete()
{
	for (Collider* collider : colliders)
		delete collider;
}

