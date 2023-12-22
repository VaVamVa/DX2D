#pragma once

class Plane : public Quad
{
private:
    const float MAP_RADIUS = 400;
    const float MAP_PUSH_SPEED = 200;    

public:
    Plane();
    ~Plane();

    void Update();    

    CircleCollider* GetCollider() { return collider; }
private:
    void Move();
    void Rotate();
    void Fire();

private:
    float speed = 100.0f;
    Vector2 direction;
    Vector2 velocity;  

    CircleCollider* collider;
};