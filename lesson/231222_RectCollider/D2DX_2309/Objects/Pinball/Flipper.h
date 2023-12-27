#pragma once

class Flipper : public Quad
{
private:
	friend class FlipperManager;
	const float MIN_ANGLE = XMConvertToRadians(+30.0f);
	const float MAX_ANGLE = XMConvertToRadians(-30.0f);

public:
	Flipper(bool isRight);
	~Flipper() = default;

	void Update() override;

	RectCollider* GetCollider() { return collider; }

private:
	void Control();

private:
	bool isRight;
	bool isSwing = false;

	float speed = 10.0f;
	float interpolationValue = 0.0f;  // º¸°£ °ª

	RectCollider* collider;
};