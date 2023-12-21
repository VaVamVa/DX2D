#include "Framework.h"
#include "Enemy.h"

Enemy::Enemy(Transform* target)
	:Quad(L"Textures/BeatShooter/rectEnemy.png", 10),
	target(target)
{
	isActive = false;
	localScale *= 0.4f;
	OBJ->Add(this);

	collider = new CircleCollider(GetSize().x * 0.5f);
	collider->SetParent(this);
}

Enemy::~Enemy()
{
	delete collider;
}

void Enemy::Update()
{
	if (!isActive)
		return;

	direction = (target->GetPos() - localPosition).GetNormalized();
	Translate(direction * moveSpeed * DELTA);

	Rotate(rotateSpeed * DELTA);

	UpdateWorld();
}

void Enemy::Spawn()
{
	isActive = true;

	Vector2 direction = RandomPos(-1.0f, 1.0f);
	localPosition = Vector2(CENTER_X, CENTER_Y) + direction.GetNormalized() * MAP_RADIUS;
}
