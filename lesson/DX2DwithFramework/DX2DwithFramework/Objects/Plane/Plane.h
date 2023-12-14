#pragma once

class Plane : public Rect
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();

private:
	void Rotation();
	void Translation();

private:
	MatrixBuffer* worldBuffer;

	Matrix world;

	Float2 pos = {}, size = { 200.0f, 200.0f };
	float angle = 0.0f;
};