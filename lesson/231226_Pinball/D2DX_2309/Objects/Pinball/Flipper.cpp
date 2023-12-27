#include "Framework.h"
#include "Flipper.h"

Flipper::Flipper(bool isRight)
	: Quad(L"Textures/Pinball/Flipper.png"), isRight(isRight)
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
