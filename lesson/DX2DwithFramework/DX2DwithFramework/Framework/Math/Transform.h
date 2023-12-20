#pragma once

class Transform
{
public:
	Transform();

	void UpdateWorld();

	void Translate(const Vector2D& velocity)
	{
		localPosition += velocity;
	}
	void Rotate(const float& angle)
	{
		localRotation.z += angle;
	}

	void SetParent(Transform* transform) { parent = transform; }

	const Vector2D GetPos() { return localPosition; };
	Vector2D GetGlobalPos() { return globalPosition; }
	Vector2D GetGlobalScale() { return globalScale; }


	bool IsActive() { return active; }
	void SetActive(bool status) { active = status; }

protected:
	std::string tag;

	Vector2D localPosition;

	Float3 localRotation = { 0, 0, 0 };

	Vector2D localScale = { 1.0f, 1.0f };

	bool active = false;

	Matrix world;

private:
	Matrix S, R, T;

	Transform* parent = nullptr;

	Vector2D globalPosition;
	Vector2D globalScale;
};