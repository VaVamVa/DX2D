#pragma once

class BulletManager : public Singleton<BulletManager>
{
private:
    const UINT SIZE = 100;

private:
    friend Singleton;
    BulletManager();

public:
    void Fire(Vector2 pos, Vector2 direction);

    bool Collide(CircleCollider* collider);

private:
    vector<class Bullet*> bullets;
};