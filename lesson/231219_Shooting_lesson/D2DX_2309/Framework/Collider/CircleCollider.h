#pragma once

class CircleCollider : public Collider
{
private:
	const UINT VERTEX_COUNT = 64;

public:
	CircleCollider(float radius = 1.0f);
	~CircleCollider() = default;

	// Collider을(를) 통해 상속됨
	virtual bool IsPointCollision(const Vector2 point) override;
	virtual bool IsCircleCollision(class CircleCollider* collider) override;
	virtual bool IsRectCollision(RectCollider* collider) override;

	float Radius() { return radius * max(GetGlobalScale().x, GetGlobalScale().y); }

private:
	float radius;

};