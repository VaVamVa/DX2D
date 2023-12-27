#include "Framework.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	Spawn();
}

void EnemyManager::CreateEnemies(Transform* target)
{
	enemies.resize(SIZE);

	for (Enemy*& enemy : enemies)
		enemy = new Enemy(target);
}

bool EnemyManager::Collision(CircleCollider* collider)
{
	for (Enemy*& enemy : enemies)
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
