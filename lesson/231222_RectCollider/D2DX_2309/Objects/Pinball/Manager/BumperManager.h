#pragma once

class BumperManager : public Singleton<BumperManager>
{
private:
	const UINT POOL_SIZE = 10;

private:
	friend Singleton;
	BumperManager();
	~BumperManager();

public:
	void CreateNewBumper(int count = 1);
	void DeactivateBumper(int count = 1);

	bool IsCollision(class Ball* ball);

	void GUIRender();

private:
	string tag = "BumperManager";

	vector<class Bumper*> bumpers;
};