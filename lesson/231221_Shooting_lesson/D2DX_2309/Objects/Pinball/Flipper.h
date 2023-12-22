#pragma once

class Flipper : public Quad
{
public:
	Flipper();
	virtual ~Flipper();

	void Update();

protected:
	virtual bool Rotate() = 0;
	

protected:
	RectCollider* collider;
};