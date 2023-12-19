#include "Framework.h"

Quad::Quad(Vector2D size)
	:size(size)
{
	Create();
}

Quad::Quad(std::wstring textureFile)
{
	texture = Texture::Add(textureFile);
	size = texture->GetSize();
	Create();
}

Quad::~Quad()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete worldBuffer;

	indices.clear();
}

void Quad::Render()
{
	if (!active)
		return;

	if (texture)
		texture->PSSet();

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Quad::Create()
{
	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,
		D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	vertexShader = VertexShader::Add(L"Shaders/VertexUV.hlsl", layoutDesc, ARRAYSIZE(layoutDesc));
	pixelShader = PixelShader::Add(L"Shaders/PixelUV.hlsl");

	float halfWidth = size.x * 0.5f;
	float halfHeight = size.y * 0.5f;

	vertices.emplace_back(-halfWidth, -halfHeight, 0, 1);
	vertices.emplace_back(-halfWidth, +halfHeight, 0, 0);
	vertices.emplace_back(+halfWidth, -halfHeight, 1, 1);
	vertices.emplace_back(+halfWidth, +halfHeight, 1, 0);

	indices = { 0, 1, 2, 2, 1, 3 };

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), indices.size());

	worldBuffer = new MatrixBuffer();
}

bool Quad::CircleCollision(Quad* target)
{
	if ((target->localPosition - localPosition).Length() < target->size.x - size.x)
		return true;
	return false;
}
