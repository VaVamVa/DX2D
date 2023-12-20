#include "Framework.h"

#include "Enemy.h"
#include "Bullet.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
	bullets.resize(POOL_SIZE);
	FOR_OBJ_P(bullets)
		ptrIter = new Bullet();
}

BulletManager::~BulletManager()
{
	FOR_OBJ_P(bullets)
		delete ptrIter;
	bullets.clear();
}

void BulletManager::Update()
{
	FOR_OBJ_P(bullets)
		ptrIter->Update();
}

void BulletManager::Render()
{
	FOR_OBJ_P(bullets)
		ptrIter->Render();
}

void BulletManager::Fire(Vector2D pos, Vector2D direction)
{
	FOR_OBJ_P(bullets)
	{
		if (!ptrIter->IsActive())
		{
			ptrIter->Fire(pos, direction);
			return;
		}
	}
}

void BulletManager::Collide(Collider* collider)
{
	/*FOR_OBJ_P(bullets)
	{
		if (ptrIter->IsActive() && ptrIter->GetCollider())
		{
			ptrIter->SetActive(false);
		}
	}*/
}
