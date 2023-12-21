#include "Framework.h"

Quad::Quad(Vector2 size) : size(size)
{
    Create();
}

Quad::Quad(wstring textureFile, int depth) : GameObject(depth)
{
    texture = Texture::Add(textureFile);
    size = texture->GetSize();

    Create();
}

Quad::~Quad()
{
    delete vertexBuffer;
    delete indexBuffer; 
}

void Quad::Render()
{
    if (!IsActive()) return;

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

    float halfWidth = size.x * 0.5f;
    float halfHeight = size.y * 0.5f;

    vertices.emplace_back(-halfWidth, -halfHeight, 0, 1);
    vertices.emplace_back(-halfWidth, +halfHeight, 0, 0);
    vertices.emplace_back(+halfWidth, -halfHeight, 1, 1);
    vertices.emplace_back(+halfWidth, +halfHeight, 1, 0);

    indices = { 0, 1, 2, 2, 1, 3 };

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(Vertex), vertices.size());
    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer();
}
