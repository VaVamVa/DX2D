#pragma once

class GameObject : public Transform
{
public:
	GameObject(int depth = 0.0f);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	int depth;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
};