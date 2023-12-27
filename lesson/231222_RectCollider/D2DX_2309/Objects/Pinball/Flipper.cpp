#include "Framework.h"
#include "Flipper.h"

Flipper::Flipper(bool isRight)
	:Quad(L"Textures/Pinball/Flipper.png", 2),
	isRight(isRight)
{
	tag = isRight ? "RightFlipper" : "LeftFlipper";
	Load();
	OBJ->Add(this);

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
	if ((isRight && KEY->Press(191))  // '?(/)'
		|| (!isRight && KEY->Press('Z')))
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

	/*if (interpolationValue == 1.0f && !isSwing)
	{
		string temp = "";
	}*/
}
