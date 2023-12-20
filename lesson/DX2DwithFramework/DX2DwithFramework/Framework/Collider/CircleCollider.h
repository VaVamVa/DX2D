#pragma once

class CircleCollider : public Collider
{
private:
	const UINT VERTEX_COUNT = 64;

public:
	CircleCollider(float radius = 1.0f);
	~CircleCollider() = default;

	bool IsCollision(Collider* collider) override;

	float Radius() { return radius * max(GetGlobalScale().x, GetGlobalScale().y); }

private:
	bool IsCircleCollision(CircleCollider* collider);

private:
	float radius;
};