#pragma once

class Ball : public CircleCollider
{
private:
	const float GRAVITY = 500.0f;
	const float ANGULAR_VELOCITY = 0.01f;

public:
	Ball(RectCollider* bgRect);
	~Ball() = default;

	void Update();

	Vector2 GetVelocity() { return velocity; }
	void SetVelocity(Vector2 velocity) { this->velocity = velocity; }
	void SetVelocity(const float x, const float y) { velocity = { x, y }; }

private:
	void CollisionBorder();

private:
	RectCollider* bgRect;
	Quad* imageQuad;

	Vector2 velocity;
};