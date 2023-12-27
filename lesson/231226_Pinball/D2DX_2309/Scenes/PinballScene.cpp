#include "Framework.h"
#include "PinballScene.h"

#include "Objects/Pinball/Bumper.h"
#include "Objects/Pinball/Flipper.h"

PinballScene::PinballScene()
{
	bg = new Quad(L"Textures/Pinball/Background.png");
	bg->SetTag("BG");
	bg->SetPos(CENTER);
	//bg->SetScale(5, SCREEN_HEIGHT);
	bg->UpdateWorld();
	bg->Load();

	Bumper* bumper = new Bumper();
	Flipper* rightFlipper = new Flipper(true);
	Flipper* leftFlipper = new Flipper(false);
}

PinballScene::~PinballScene()
{
}

void PinballScene::Update()
{	
}

void PinballScene::Render()
{
}

void PinballScene::PostRender()
{
}
