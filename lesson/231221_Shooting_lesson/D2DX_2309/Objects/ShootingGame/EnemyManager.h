#pragma once

#include "Enemy.h"

class EnemyManager : public Singleton<EnemyManager>
{
private:
	const UINT SIZE = 100;
	const float SPAWN_INTERVAL = 1.0f;

public:
	EnemyManager();
	~EnemyManager();

	void Update();

	void CreateEnemies(Transform* target);

	bool Collision(CircleCollider* collider);

private:
	void Spawn();

private:
	vector<Enemy*> enemies;

	float time = 0.0f;
};