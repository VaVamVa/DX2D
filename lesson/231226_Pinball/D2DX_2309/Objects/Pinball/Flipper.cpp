#include "Framework.h"

#include "Ball.h"
#include "Flipper.h"

Flipper::Flipper(bool isRight)
	: Quad(L"Textures/Pinball/Flipper.png", 6), isRight(isRight)
{
	tag = isRight ? "RightFlipper" : "LeftFlipper";
	Load();

	collider = new RectCollider(GetSize());
	collider->SetParent(this);
	collider->SetTag(tag + "Collider");
	collider->Load();
}

void Flipper::Update()
{
	Control();

	CollisionBall();

	UpdateWorld();
}

void Flipper::Control()
{
	if ((isRight && KEY->Press(VK_RBUTTON))
		|| (!isRight && KEY->Press(VK_LBUTTON)))
	{
		interpolationValue += speed * DELTA;
		isSwing = interpolationValue < 1.0f;
	}
	else
	{
		interpolationValue -= speed * DELTA;
		isSwing = false;
	}

	interpolationValue = Clamp(0.0f, 1.0f, interpolationValue);
	localRotation.z = Lerp(MIN_ANGLE, MAX_ANGLE, interpolationValue);
}

void Flipper::CollisionBall()
{
	if (!collider->IsCircleCollision(ball))
		return;

	// 플리퍼의 법선 벡터
	Vector2 normal = GetUp();
	// 반사벡터
	Vector2 reflectVector = (ball->GetVelocity() + normal * 2.0f * Dot(ball->GetVelocity() * -1.0f, normal)).GetNormalized();

	float power = 0.0f;
	float distanceRate = 0.0f;

	if (isSwing)
	{
		float rate = interpolationValue + 1.0f;

		/*
		o			a
		=================|OOOO
		o와 a 타점에 따라 가해지는 힘이 다르다.
		*/
		distanceRate = Distance(ball->GetPos(), collider->RightTop()) / GetSize().x;

		Clamp(0.0f, 1.0f, distanceRate);
		power = rate * ball->GetVelocity().Length() + distanceRate;

		//ball->SetVelocity(normal * power);
	}
	else
	{
		power = ball->GetVelocity().Length() * BOUND_FORCE_FACTOR;
	}

	ball->SetVelocity(reflectVector * power);
	
	Vector2 edgeToBallVector = ball->GetGlobalPos() - collider->LeftTop();
	/*
	float distance = Clamp(0.0f, collider->Size().x, Dot(edgeToBallVector, GetRight()));

	// 접점
	Vector2 contactPos = collider->LeftTop() + GetRight() * distance;

	ball->SetPos(contactPos + normal * ball->Radius());
	*/

	float overlap = ball->Radius() - Dot(normal, edgeToBallVector);
	ball->Translate(GetUp() * overlap);
}
