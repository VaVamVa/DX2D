#include "Framework.h"
#include "PinballScene.h"

#include "Objects/Pinball/Flipper.h"
#include "Objects/Pinball/LeftFlipper.h"
#include "Objects/Pinball/RightFlipper.h"

PinballScene::PinballScene()
{
	/*GameObject* bg = OBJ->Add(new Quad(L"Textures/Pinball/pinballBG.png"));
	bg->SetPos(CENTER);
	bg->SetScale(2, 2);
	bg->UpdateWorld();*/

	left = (Flipper*)OBJ->Add(new LeftFlipper());
	left->SetTag("Left");
	right = (Flipper*)OBJ->Add(new RightFlipper());
	right->SetTag("Right");
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
