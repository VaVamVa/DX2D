#include "Framework.h"
#include "Enemy.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	for (Enemy*& enemy : enemies)
		delete enemy;
}

void EnemyManager::Update()
{
	Spawn();
}

void EnemyManager::CreateEnemies(Transform* target)
{
	enemies.resize(POOL_SIZE);

	for (Enemy*& enemy : enemies)
		enemy = new Enemy(target);
}

bool EnemyManager::IsCollision(CircleCollider* collider)
{
	for (Enemy* enemy : enemies)
	{
		if (enemy->GetCollider()->IsCircleCollision(collider))
		{
			enemy->SetActive(false);
			return true;
		}
	}
	return false;
}

void EnemyManager::Spawn()
{
	time += DELTA;

	if (time > SPAWN_INTERVAL)
	{
		time -= SPAWN_INTERVAL;

		for (Enemy*& enemy : enemies)
		{
			if (!enemy->IsActive())
			{
				enemy->Spawn();
				return;
			}
		}
	}
}
