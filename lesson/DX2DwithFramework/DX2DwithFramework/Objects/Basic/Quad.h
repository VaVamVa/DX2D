#pragma once

class Quad : public GameObject
{
public:
	Quad(Vector2D size);
	Quad(std::wstring textureFile, int depth = 0);
	~Quad();

	void Render();

	void Create();

	bool CircleCollision(Quad* target);

protected:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	std::vector<VertexUV> vertices;
	std::vector <UINT> indices;

	Texture* texture = nullptr;

	Vector2D size;
};