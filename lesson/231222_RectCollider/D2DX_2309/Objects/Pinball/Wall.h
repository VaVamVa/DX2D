#pragma once

class Wall : public Quad
{
private:
	friend class WallManager;

public:
	Wall(int index);
	~Wall() = default;

	RectCollider* GetCollider() { return collider; }

private:
	RectCollider* collider;
};