#pragma once

class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 position;
		Vector2 axis[2];
		Vector2 halfSize;
	};

public:
	RectCollider(Vector2 size);
	~RectCollider() = default;

	virtual bool IsPointCollision(const Vector2& point) override;
	virtual bool IsCircleCollision(CircleCollider* collider) override;
	virtual bool IsRectCollision(RectCollider* collider) override;

	Vector2 Size() { return size * GetGlobalScale(); }
	Vector2 Half() { return Size() * 0.5f; }

	Vector2 LeftTop();
	Vector2 LeftBottom();
	Vector2 RightTop();
	Vector2 RightBottom();

	ObbDesc GetObb();

private:
	bool IsSeperate(Vector2 seperateAxis, ObbDesc box1, ObbDesc box2);

private:
	Vector2 size;
};