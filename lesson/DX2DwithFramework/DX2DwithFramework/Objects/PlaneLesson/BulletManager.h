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

	void Fire(Vector2D pos, Vector2D direction);

private:
	std::vector<class Bullet*> bullets;
};