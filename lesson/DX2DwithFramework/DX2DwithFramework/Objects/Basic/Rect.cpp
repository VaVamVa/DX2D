#include "Framework.h"

Rect::Rect(Float2 size)
{
	vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
	pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

	float halfWidth = size.x * 0.5f;
	float halfHeight = size.y * 0.5f;

	vertices.emplace_back(-halfWidth, -halfHeight, 1, 0, 0);
	vertices.emplace_back(-halfWidth, +halfHeight, 0, 1, 0);
	vertices.emplace_back(+halfWidth, -halfHeight, 0, 0, 1);
	vertices.emplace_back(+halfWidth, +halfHeight, 0, 1, 1);

	indices = { 0, 1, 2, 2, 1, 3 };

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

Rect::~Rect()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete indexBuffer;

	indices.clear();
}

void Rect::Render()
{
	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}
