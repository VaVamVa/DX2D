#pragma once

class Bumper : public Quad
{
public:
	Bumper();
	~Bumper() = default;

private:
	vector<RectCollider*> colliders;
};