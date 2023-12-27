#include "Framework.h"
#include "Ball.h"

Ball::Ball(RectCollider* bgRect)
	:bgRect(bgRect),
	CircleCollider(20)
{
	localPosition = CENTER;

	imageQuad = new Quad(L"Textures/Pinball/Ball.png", 9);
	imageQuad->SetParent(this);
	imageQuad->SetTag("BallImage");
	imageQuad->Load();
}

void Ball::Update()
{
	CollisionBorder();

	velocity.y -= GRAVITY * DELTA;

	Translate(velocity * DELTA);
	Rotate(velocity.Length() * ANGULAR_VELOCITY * DELTA);
}

void Ball::CollisionBorder()
{
	if (IsRectCollision(bgRect))
	{
		if (GetGlobalPos().x < bgRect->LeftTop().x)
			velocity.x *= -1.0f;
		if (GetGlobalPos().x > bgRect->RightTop().x)
			velocity.x *= -1.0f;
		if (GetGlobalPos().y > bgRect->RightTop().y)
			velocity.y *= -1.0f;
	}
}
