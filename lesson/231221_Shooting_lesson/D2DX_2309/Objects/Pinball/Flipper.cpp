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
	// Ư�� ��Ȳ������ UpdateWorld();
}
