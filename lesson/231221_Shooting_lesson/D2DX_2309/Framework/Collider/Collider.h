#pragma once

class Collider : public Transform
{
protected:
	enum class Type
	{
		RECT, CIRCLE
	};

public:
	Collider();
	~Collider();

	void Render();	

	bool IsCollision(Collider* collider);

	virtual bool IsPointCollision(const Vector2& point) = 0;
	virtual bool IsCircleCollision(class CircleCollider* collider) = 0;
	virtual bool IsRectCollision(class RectCollider* collider) = 0;

	void SetColor(float r, float g, float b) { colorBuffer->Set(r, g, b); }
public:
	static void TotalUpdate();
	static void TotalRender();
	static void Delete();

protected:
	Type type;

	VertexBuffer* vertexBuffer;
	vector<VertexPos> vertices;

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	static vector<Collider*> colliders;
	static bool isDraw;
};