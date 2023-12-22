#include "Framework.h"
#include "Flipper.h"
#include "LeftFlipper.h"

LeftFlipper::LeftFlipper()
{
	localRotation.y = XM_PI;
	localPosition = { CENTER_X - GetSize().x, CENTER_Y };
}

LeftFlipper::~LeftFlipper()
{
}

void LeftFlipper::Rotate()
{
}
