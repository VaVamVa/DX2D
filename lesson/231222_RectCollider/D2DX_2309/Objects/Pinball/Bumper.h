#pragma once

class Bumper : public Quad
{
public:
	Bumper(int index);
	~Bumper() = default;

	Vector2 Repulse(Vector2 direction);
	bool IsCollision(class Ball* ball);

private:
	vector<RectCollider*> colliders;
};