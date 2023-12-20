#pragma once

class Collider : public Transform
{
public:
	Collider();
	virtual ~Collider();

	void Render();

	virtual bool IsCollision(Collider* collider) = 0;

	static void TotalUpdate();
	static void TotalRender();
	
protected:
	VertexBuffer* vertexBuffer;
	std::vector<VertexPos> vertices;

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	static std::set<Collider*> colliders;
};