#pragma once

class Collider : public Transform
{
public:
	Collider();
	~Collider();

	void Render();

	bool IsCollision(Collider* collider);

	virtual bool IsCircleCollision(class CircleCollider* collider) = 0;

	static void TotalUpdate();
	static void TotalRender();
	static void Delete();

protected:
	VertexBuffer* vertexBuffer;
	vector<VertexPos> vertices;

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	static vector<Collider*> colliders;
};