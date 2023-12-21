#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(int depth) : depth(depth)
{
	vertexShader = Shader::AddVS(L"VertexUV.hlsl");
	pixelShader = Shader::AddPS(L"PixelUV.hlsl");

	worldBuffer = new MatrixBuffer();
}

GameObject::~GameObject()
{
	delete worldBuffer;
}

void GameObject::SetPS(wstring file)
{
	pixelShader = Shader::AddPS(file);
}
