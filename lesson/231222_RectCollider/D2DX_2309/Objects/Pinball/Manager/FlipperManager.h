#pragma once

class FlipperManager : public Singleton<FlipperManager>
{
private:
	const float POWER = 10.0f;

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