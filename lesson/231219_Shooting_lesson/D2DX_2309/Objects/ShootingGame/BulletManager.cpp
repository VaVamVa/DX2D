#include "Framework.h"
#include "Bullet.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
    bullets.resize(SIZE);

    for (Bullet*& bullet : bullets)
        bullet = new Bullet();
}

void BulletManager::Fire(Vector2 pos, Vector2 direction)
{
    for (Bullet*& bullet : bullets)
    {
        if (!bullet->IsActive())
        {
            bullet->Fire(pos, direction);
            return;
        }
    }
}

