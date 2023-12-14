#pragma once

class Rect
{
public:
	Rect(Float2 size);
	~Rect();

	void Render();

protected:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	std::vector<Vertex> vertices;
	std::vector <UINT> indices;
};