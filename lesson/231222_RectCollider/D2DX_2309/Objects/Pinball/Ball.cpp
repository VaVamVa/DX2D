#include "Framework.h"
#include "Ball.h"

#include "Manager/BumperManager.h"
#include "Manager/WallManager.h"
#include "Manager/FlipperManager.h"
#include "Flipper.h"

Ball::Ball()
	:Quad(L"Textures/Pinball/Ball.png", 3)
{
	tag = "Ball";
	Load();
	OBJ->Add(this);

	collider = new CircleCollider(GetSize().x);
	collider->SetTag("BallCollider");
	collider->SetParent(this);
	collider->Load();

	localPosition.x = Random::Get()->Range(130.0f + size.x, 470.0f - size.x);
	localPosition.y = 600.0f;
	UpdateWorld();
}

void Ball::Update()
{
	CollideCheck();

	velocity.y -= GRAVITY * DELTA;

	if (localPosition.y - GetSize().y <= 0)
		velocity.y = 0.0f;
	Translate(velocity);
	UpdateWorld();
}

void Ball::CollideCheck()
{
	FlipperManager::Get()->IsCollision(this);
	BumperManager::Get()->IsCollision(this);
	WallManager::Get()->IsCollision(this);
}
