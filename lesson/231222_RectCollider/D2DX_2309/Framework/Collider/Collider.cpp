#include "Framework.h"

vector<Collider*> Collider::colliders;
bool Collider::isDraw = true;

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
	delete vertexBuffer;

	delete colorBuffer;
	delete worldBuffer;
}

void Collider::Render()
{
	if (!IsActive()) return;

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
	if (!IsActive() || !collider->IsActive()) return false;

	switch (collider->type)
	{
	case Collider::Type::RECT:
		return IsRectCollision((RectCollider*)collider);
	case Collider::Type::CIRCLE:
		return IsCircleCollision((CircleCollider*)collider);	
	}

	return false;
}

void Collider::TotalUpdate()
{
	if (KEY->Down(VK_F1))
		isDraw = !isDraw;

	for (Collider* collider : colliders)
		collider->UpdateWorld();
}

void Collider::TotalRender()
{
	if (!isDraw) return;

	for (Collider* collider : colliders)
		collider->Render();
}

void Collider::Delete()
{
	for (Collider* collider : colliders)
		delete collider;
}
