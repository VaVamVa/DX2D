#pragma once

class Plane : public Quad
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();

private:
	void Move();
	void Aim();

	void Fire();

private:
	float speed = 200.0f;
	Vector2D direction;

	Vector2D velocity;
};