#pragma once

class PlaneL : public Quad
{
public:
	PlaneL();
	~PlaneL();

	void Update();
	void Render();

private:
	void Move();
	void Rotate();

	void Fire();

private:
	float speed = 100.0f;
	Vector2D direction;
};