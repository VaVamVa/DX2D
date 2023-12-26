#pragma once

class Enemy : public Quad
{
private:
	const float MAP_RADIUS = 400;
public:
	Enemy(Transform* target);
	~Enemy();

	virtual void Update() override;

	void Spawn();

	CircleCollider* GetCollider() { return collider; }

private:
	CircleCollider* collider;
	Transform* target;

	float moveSpeed = 50.0f;
	float rotSpeed = 10.0f;

	Vector2 direction;
};