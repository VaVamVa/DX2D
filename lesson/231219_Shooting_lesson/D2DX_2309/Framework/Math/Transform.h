#pragma once

class Transform
{
public:
    Transform();

    void UpdateWorld();
    void GUIRender();

    bool IsActive();
    void SetActive(bool isActive) { this->isActive = isActive; }

    void Translate(const Vector2& velocity)
    {
        localPosition += velocity;
    }
    void Rotate(const float& angle)
    {
        localRotation.z += angle;
    }

    void SetParent(Transform* transform) { parent = transform; }

    Vector2 GetPos() { return localPosition;}
    float GetAngle() { return localRotation.z; }
    Vector2 GetScale() { return localScale; }

    void SetPos(Vector2 pos) { localPosition = pos; }
    void SetPos(float x, float y) { localPosition = { x, y }; }
    void SetRot(Float3 rot) { localRotation = rot; }
    void SetAngle(float angle) { localRotation.z = angle; }
    void SetScale(Vector2 scale) { localScale = scale; }
    void SetScale(float x, float y) { localScale = { x, y }; }

    Vector2 GetGloabalPos() { return globalPosition; }
    Vector2 GetGlobalScale() { return globalScale; }

protected:
    string tag;

    Vector2 localPosition;
    Float3 localRotation = { 0, 0, 0 };
    Vector2 localScale = { 1, 1 };

    bool isActive = true;

    Matrix world;

private:
    Matrix S, R, T;

    Transform* parent = nullptr;

    Vector2 globalPosition;
    Vector2 globalScale;
};