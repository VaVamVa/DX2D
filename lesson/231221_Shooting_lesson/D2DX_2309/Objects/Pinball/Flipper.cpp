#include "Framework.h"
#include "Flipper.h"

Flipper::Flipper()
	:Quad(L"Textures/Pinball/flipper.png", 6)
{
	
}

Flipper::~Flipper()
{
}

void Flipper::Update()
{
	Rotate();
	// 특정 상황에서만 UpdateWorld();
}
