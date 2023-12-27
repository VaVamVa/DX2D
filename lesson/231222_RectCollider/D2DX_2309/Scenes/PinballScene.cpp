#include "Framework.h"
#include "PinballScene.h"

#include "Objects/Pinball/Ball.h"
#include "Objects/Pinball/Manager/BumperManager.h"
#include "Objects/Pinball/Manager/FlipperManager.h"
#include "Objects/Pinball/Manager/WallManager.h"

PinballScene::PinballScene()
{
	CreateBg();

	BumperManager::Get()->CreateNewBumper();
	FlipperManager::Get();
	WallManager::Get();
	Ball* ball = new Ball();
}

PinballScene::~PinballScene()
{
}

void PinballScene::Update()
{
}

void PinballScene::Render()
{
	bg->Render();
}

void PinballScene::PostRender()
{
	BumperManager::Get()->GUIRender();
}

void PinballScene::CreateBg()
{
	bg = new Quad(L"Textures/Pinball/BG.png");
	bg->SetTag("BG");
	bg->SetPos(CENTER);
	bg->Load();
	bg->UpdateWorld();
}
