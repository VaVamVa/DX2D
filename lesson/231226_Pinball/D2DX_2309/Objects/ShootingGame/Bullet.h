#pragma once

class Bullet : public Quad
{
private:
    const float MAP_RADIUS = 400;

public:
    Bullet();
    ~Bullet();

    void Update();

    void Fire(Vector2 pos, Vector2 direction);

    CircleCollider* GetCollider() { return collider; }

private:
    float speed = 500;
    Vector2 direction;

    CircleCollider* collider;
};