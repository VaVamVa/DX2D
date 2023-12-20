#include "Framework.h"

std::set<Collider*> Collider::colliders;

Collider::Collider()
{
	vertexShader = Shader::AddVS(L"VertexPos.hlsl");
	pixelShader = Shader::AddPS(L"PixelPos.hlsl");

	worldBuffer = new MatrixBuffer();

	colorBuffer = new ColorBuffer();
	colorBuffer->Set(0.0f, 1.0f, 0.0f);

	colliders.insert(this);

}

Collider::~Collider()
{
	delete vertexBuffer;
	delete worldBuffer;
	delete colorBuffer;

	colliders.erase(this);
}

void Collider::Render()
{
	if (!active) return;

	colorBuffer->SetPS(0);

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	vertexShader->Set();
	pixelShader->Set();

	DC->Draw(vertices.size(), 0);
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
