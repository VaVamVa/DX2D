#include "Framework.h"

#include "Bullet.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
	bullets.resize(POOL_SIZE);
	FOR_OBJ_P(bullets)
		iter = new Bullet();
}

BulletManager::~BulletManager()
{
	FOR_OBJ_P(bullets)
		delete iter;
	bullets.clear();
}

void BulletManager::Update()
{
	FOR_OBJ_P(bullets)
		iter->Update();
}

void BulletManager::Render()
{
	FOR_OBJ_P(bullets)
		iter->Render();
}

void BulletManager::Fire(Vector2D pos, Vector2D direction)
{
	FOR_OBJ_P(bullets)
	{
		if (!iter->IsActive())
		{
			iter->Fire(pos, direction);
			return;
		}
	}
}
