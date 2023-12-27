#pragma once

class Ball : public Quad
{
private:
	const float GRAVITY = 9.8f;

public:
	Ball();
	~Ball() = default;

	void Update() override;

	CircleCollider* GetCollider() { return collider; }

	Vector2 GetVelocity() { return velocity; }
	void SetVelocity(Vector2 direction) { this->velocity = direction; }

private:

	void CollideCheck();

private:
	CircleCollider* collider;

	Vector2 velocity = { 0.0f, 0.0f };
};