#pragma once

class Plane : public Quad
{
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
};