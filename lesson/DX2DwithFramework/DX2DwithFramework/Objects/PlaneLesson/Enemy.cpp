#include "Framework.h"
#include "Enemy.h"
#include "BulletManager.h"

Enemy::Enemy(std::wstring name)
	:Quad(L"Textures/BeatShooter/" + name + L".png")
{
}

void Enemy::Update()
{
	if (!active) return;

	BulletManager::Get()->Collide(this);

	Rotate();
	Move();

	UpdateWorld();
}

void Enemy::Spawn(std::vector<float>& status)
{
	int cardinalPoints = RAND->GetRandomInt(1, 4);

	switch (cardinalPoints)
	{
	case 1:
		localPosition.x = SCREEN_WIDTH + size.x;
		localPosition.y = RAND->GetRandomFloat(size.y, SCREEN_HEIGHT - size.y);
		break;
	case 2:
		localPosition.x = - size.x;
		localPosition.y = RAND->GetRandomFloat(size.y, SCREEN_HEIGHT - size.y);
		break;
	case 3:
		localPosition.x = RAND->GetRandomFloat(size.x, SCREEN_WIDTH - size.x);
		localPosition.y = SCREEN_HEIGHT + size.y;
		break;
	case 4:
		localPosition.x = RAND->GetRandomFloat(size.x, SCREEN_WIDTH - size.x);
		localPosition.y = - size.y;
		break;
	}

	active = true;
	curHp = status[0];
	power = status[1];
	moveSpeed = status[2];
	spawnInterval = status[3];

}

void Enemy::Damage(int power)
{
	curHp -= power;
	if (curHp <= 0)
		active = false;
}

void Enemy::Rotate()
{
	localRotation.z += DELTA;
}

void Enemy::Move()
{
	direction = (target->GetPos() - localPosition).GetNormalized();
	localPosition += direction * moveSpeed * DELTA;
}
