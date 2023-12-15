#pragma once

class BulletManager : public Singleton<BulletManager>
{
private:
	const int POOL_SIZE = 50;

private:
	friend Singleton;
	BulletManager();
	~BulletManager();

public:
	void Update();
	void Render();

	void Fire(Float2 pos, float direction);

private:
	std::vector<class Bullet*> bullets;
};