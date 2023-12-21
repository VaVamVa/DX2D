#pragma once

class RectCollider : public Collider
{
public:
	RectCollider(Vector2 size);
	RectCollider(float x, float y) : size(Vector2(x, y)) { type = Type::RECT; }
	~RectCollider() = default;

	// Collider을(를) 통해 상속됨
	virtual bool IsPointCollision(const Vector2 point) override;
	virtual bool IsCircleCollision(CircleCollider* collider) override;
	virtual bool IsRectCollision(RectCollider* collider) override;

	Vector2 Size() { return size * GetGlobalScale(); }
	Vector2 Half() { return Size() * 0.5f; }

	Vector2 LeftTop();
	Vector2 LeftBottom();
	Vector2 RightTop();
	Vector2 RightBottom();

private:
	Vector2 size;
};