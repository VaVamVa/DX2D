#pragma once

#include "Bullet.h"

class BulletManager : public Singleton<BulletManager>
{
private:
    const UINT SIZE = 100;

public:
    BulletManager();

    void Fire(Vector2 pos, Vector2 direction);

private:
    vector<Bullet*> bullets;
};