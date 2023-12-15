#pragma once

class Bullet
{
private:
	const float SPEED = 200.0f;

public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

	void Fire(Float2 pos, float direction);

	bool IsActive() { return active; }

private:
	void Translation();
	void Destroy();


private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	std::vector<VertexColor> vertices;
	std::vector <UINT> indices;

	MatrixBuffer* worldBuffer;
	Matrix world;

	bool active = false;

	Float2 pos = {};
	float angle = 0.0f;
};
