#pragma once

class FlipperManager : public Singleton<FlipperManager>
{
private:
	const float POWER = 980.0f;
	const float PUSH_LAND_POWER = 300.0f;

private:
	friend Singleton;
	FlipperManager();
	~FlipperManager() = default;

public:
	bool IsCollision(class Ball* ball);

private:
	class Flipper* leftFlipper;
	class Flipper* rightFlipper;
};