#pragma once

class WallManager : public Singleton<WallManager>
{
private:
	const UINT POOL_SIZE = 10;
	const float PUSH_LAND_POWER = 200.0f;

private:
	friend Singleton;
	WallManager();
	~WallManager();

public:
	void Render();

	bool IsCollision(class Ball* ball);

private:
	vector<class Wall*> walls;
};