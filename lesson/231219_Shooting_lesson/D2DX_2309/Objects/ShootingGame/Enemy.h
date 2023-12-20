#pragma once

class Enemy : public Quad
{
private:
	const float MAP_RADIUS = 400.0f;

public:
	Enemy(Transform* target);
	~Enemy();

	virtual void Update() override;

	void Spawn();

	CircleCollider* GetCollider() { return collider; }

private:
	Transform* target;

	float moveSpeed = 50.0f;
	float rotateSpeed = 10.0f;
	Vector2 direction;

	CircleCollider* collider;
};