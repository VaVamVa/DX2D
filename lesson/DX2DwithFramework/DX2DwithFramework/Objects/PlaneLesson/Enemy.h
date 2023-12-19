#pragma once

class Enemy : public Quad
{
public:
	Enemy(std::wstring name);
	~Enemy() = default;

	void Update();

	virtual void Spawn(std::vector<float>&);
	void Damage(int power);

	void SetTarget(Quad* target) { this->target = target; }

protected:
	virtual void Rotate();
	virtual void Move();

protected:
	Quad* target = nullptr;

	Vector2D direction;

	float curHp = 0;
	float power = 0;
	float moveSpeed = 0;
	float spawnInterval = 0;
};
