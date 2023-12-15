#pragma once

class Bullet : public Quad
{
public:
	Bullet();
	~Bullet() = default;

	void Update();
	void Render();

	void Fire(Vector2D pos, Vector2D direction);

private:
	float speed = 500.0f;
	Vector2D direction;
};