#pragma once

class Plane : public Quad
{
private:
    const float MAP_RADIUS = 400.0f;
    const float MAP_PUSH_SPEED = 200.0f;
    const Vector2 CENTER = { CENTER_X, CENTER_Y };

public:
    Plane();
    ~Plane();

    void Update();    

private:
    void Move();
    void Rotate();
    void Fire();

private:
    float speed = 100.0f;
    Vector2 direction;
    Vector2 velocity;

    Collider* collider;
};