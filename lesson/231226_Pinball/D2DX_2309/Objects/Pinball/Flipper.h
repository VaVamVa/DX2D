#pragma once

class Flipper : public Quad
{
private:	
	const float MIN_ANGLE = XMConvertToRadians(+30.0f);
	const float MAX_ANGLE = XMConvertToRadians(-30.0f);	

public:
	Flipper(bool isRight);

	void Update() override;	

	RectCollider* GetCollider() { return collider; }

private:
	void Control();

private:
	bool isRight;
	bool isSwing = false;

	float speed = 10.0f;
	float interpolationValue = 0.0f;

	RectCollider* collider;
};