#include "SCENELOGO.h"

SCENELOGO::SCENELOGO()
{
	mScene = new LogoObject(L"Logo", Vector(0, 0));
	Aninum = 0; Delttime = 0;
	GET_TIMEMANAGER->SetPreTime();
}

SCENELOGO::~SCENELOGO()
{
	delete mScene;
}

void SCENELOGO::Init()
{

}

void SCENELOGO::Update()
{
	GET_TIMEMANAGER->SetCurTime();
	Delttime += DELTATIME;
}

void SCENELOGO::Render()
{
	if (Delttime < 2) {
		Aninum++;
		mScene->Render(Aninum % 8);
	}
	else GET_SCENEMANAGER->SwitchScene(SceneManager::e_SceneType::Menu);
}

void SCENELOGO::Destroy()
{

}