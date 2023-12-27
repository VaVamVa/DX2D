#include "Framework.h"
#include "PinballScene.h"

#include "Objects/Pinball/Ball.h"
#include "Objects/Pinball/Bumper.h"
#include "Objects/Pinball/Flipper.h"

PinballScene::PinballScene()
{
	bg = new Quad(L"Textures/Pinball/Background.png");
	bg->SetTag("BG");
	bg->SetPos(CENTER);
	//bg->SetScale(5, SCREEN_HEIGHT);
	bg->Load();

	RectCollider* bgRect = new RectCollider(bg->GetSize());
	bgRect->SetParent(bg);

	Bumper* bumper = new Bumper();
	Flipper* rightFlipper = new Flipper(true);
	Flipper* leftFlipper = new Flipper(false);

	ball = new Ball(bgRect);
	rightFlipper->SetBall(ball);
	leftFlipper->SetBall(ball);
}

PinballScene::~PinballScene()
{
}

void PinballScene::Update()
{	
	ball->Update();
}

void PinballScene::Render()
{
}

void PinballScene::PostRender()
{
}
