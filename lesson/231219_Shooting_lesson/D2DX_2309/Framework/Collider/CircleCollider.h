#pragma once

class CircleCollider : public Collider
{
private:
	const UINT VERTEX_COUNT = 64;

public:
	CircleCollider(float radius = 1.0f);
	~CircleCollider() = default;

	bool IsCircleCollision(class CircleCollider* collider) override;

	float Radius() { return radius * max(GetGlobalScale().x, GetGlobalScale().y); }

private:
	float radius;
};