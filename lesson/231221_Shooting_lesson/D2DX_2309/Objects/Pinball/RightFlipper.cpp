#include "Framework.h"
#include "Flipper.h"
#include "RightFlipper.h"

RightFlipper::RightFlipper()
{
	localPosition = { CENTER_X + GetSize().x, CENTER_Y };
}

RightFlipper::~RightFlipper()
{
}

void RightFlipper::Rotate()
{
}
