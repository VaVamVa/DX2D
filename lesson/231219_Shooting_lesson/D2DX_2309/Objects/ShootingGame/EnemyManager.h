#pragma once

class EnemyManager : public Singleton<EnemyManager>
{
private:
	const UINT POOL_SIZE = 100;
	const float SPAWN_INTERVAL = 1.0f;

private:
	friend Singleton;
	EnemyManager();
	~EnemyManager();

public:
	void Update();

	void CreateEnemies(Transform* target);

	void Collision(CircleCollider* collider);

private:
	void Spawn();

private:
	vector<class Enemy*> enemies;

	float time = 0.0f;
};