#pragma once

class Quad : public Transform
{
public:
	Quad(Vector2D size);
	Quad(std::wstring textureFile);
	~Quad();

	void Render();

	void Create();

	bool CircleCollision(Quad* target);

protected:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	std::vector<VertexUV> vertices;
	std::vector <UINT> indices;

	MatrixBuffer* worldBuffer;

	Texture* texture = nullptr;

	Vector2D size;
};