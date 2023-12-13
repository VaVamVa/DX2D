#pragma once

class TutorialScene :public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	MatrixBuffer* worldBuffer;
	MatrixBuffer* viewBuffer;
	MatrixBuffer* projectionBuffer;

	std::vector<Vertex> vertices;
	std::vector <UINT> indices;
};