#include "Framework.h"
#include "PinballScene.h"

#include "Objects/Pinball/Bumper.h"
#include "Objects/Pinball/Flipper.h"

PinballScene::PinballScene()
{
	bg = new Quad(L"Textures/Pinball/BG.png");
	bg->SetTag("BG");
	bg->SetPos(CENTER);
	//bg->SetScale(SCREEN_WIDTH, SCREEN_HEIGHT);
	bg->Load();
	bg->UpdateWorld();

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
