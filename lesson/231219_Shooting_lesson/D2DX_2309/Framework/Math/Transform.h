#pragma once

class Transform
{
public:
    Transform();

    void UpdateWorld();

    bool IsActive() { return isActive; }
    void SetActive(bool isActive) { this->isActive = isActive; }

    Vector2 GetPos() { return localPosition;}
    float GetAngle() { return localRotation.z; }
    Vector2 GetScale() { return localScale; }

    void SetPos(Vector2 pos) { localPosition = pos; }
    void SetPos(float x, float y) { localPosition = { x, y }; }
    void SetRot(Float3 rot) { localRotation = rot; }
    void SetAngle(float angle) { localRotation.z = angle; }
    void SetScale(Vector2 scale) { localScale = scale; }
    void SetScale(float x, float y) { localScale = { x, y }; }

protected:
    string tag;

    Vector2 localPosition;
    Float3 localRotation = { 0, 0, 0 };
    Vector2 localScale = { 1, 1 };

    bool isActive = true;

    Matrix world;

private:
    Matrix S, R, T;
};