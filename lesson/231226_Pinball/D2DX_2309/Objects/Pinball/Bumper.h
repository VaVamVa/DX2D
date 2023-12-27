#pragma once

class Bumper : public Quad
{
public:
	Bumper();

private:
	vector<RectCollider*> colliders;
};