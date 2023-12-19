#include "Framework.h"
#include "Enemy.h"
#include "BulletManager.h"
#include "Scenes/PlaneSceneLesson.h"

Enemy::Enemy(std::wstring name)
	:Quad(L"Textures/BeatShooter/" + name + L".png")
{
}

void Enemy::Update()
{
	if (!active) return;

	if (BulletManager::Get()->Collide(this))
		PlaneSceneLesson::GetScore();

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

	curHp = status[0];
	power = status[1];
	moveSpeed = status[2];
	spawnInterval = status[3];
	active = true;

	UpdateWorld();
}

void Enemy::Damage(int power)
{
	curHp -= power;
	if (curHp <= 0)
		active = false;
}

void Enemy::Rotate()
{
	localRotation.z += DELTA * moveSpeed / ROLLING_SPEED_FACTOR;
}

void Enemy::Move()
{
	direction = (target->GetPos() - localPosition).GetNormalized();
	localPosition += direction * moveSpeed * DELTA;
}
