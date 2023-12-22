#pragma once

class Transform
{
public:
    Transform();

    void UpdateWorld();
    void GUIRender();

    void Translate(const Vector2& velocity)
    {
        localPosition += velocity;
    }
    void Rotate(const float& angle)
    {
        localRotation.z += angle;
    }

    void SetParent(Transform* transform) { parent = transform; }
    
    void SetTag(string tag) { this->tag = tag; }

    bool IsActive();
    void SetActive(bool isActive) { this->isActive = isActive; }

    Vector2 GetPos() { return localPosition;}
    float GetAngle() { return localRotation.z; }
    Vector2 GetScale() { return localScale; }

    Vector2 GetRight() { return rightVector.GetNormalized(); }
    Vector2 GetUp() { return upVector.GetNormalized(); }

    void SetPos(Vector2 pos) { localPosition = pos; }
    void SetPos(float x, float y) { localPosition = { x, y }; }
    void SetRot(Float3 rot) { localRotation = rot; }
    void SetAngle(float angle) { localRotation.z = angle; }
    void SetScale(Vector2 scale) { localScale = scale; }
    void SetScale(float x, float y) { localScale = { x, y }; }

    void SetPivot(float x, float y) { pivot = { x, y }; }

    Vector2 GetGlobalPos() { return globalPosition; }
    Vector2 GetGlobalScale() { return globalScale; }

protected:
    string tag;

    Vector2 localPosition;
    Float3 localRotation = { 0, 0, 0 };
    Vector2 localScale = { 1, 1 };

    Vector2 pivot;

    bool isActive = true;

    Matrix world;

private:
    Matrix S, R, T, P, invP;

    Transform* parent = nullptr;

    Vector2 globalPosition, globalScale;
    Vector2 rightVector, upVector;

    XMFLOAT4X4 matWorld;
};