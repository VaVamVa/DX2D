#pragma once

class Plane : public Quad
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();

private:
	void Rotation();
	void Translation();
	void Fire();

private:
	MatrixBuffer* worldBuffer;

	Matrix world;

	Float2 pos = {}, size = { 200.0f, 200.0f };
	float angle = 0.0f;
};