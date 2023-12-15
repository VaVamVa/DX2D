#pragma once

class Transform
{
public:
	Transform();

	void UpdateWorld();

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
};