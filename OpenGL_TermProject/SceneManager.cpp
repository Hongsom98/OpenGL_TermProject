#include "SceneManager.h"

SCENEMANAGER::SCENEMANAGER()
	: CurScene(nullptr)
{

}

SCENEMANAGER::~SCENEMANAGER()
{

}

void SCENEMANAGER::Init() {
	CurScene = new SCENELOGO;
}

void SCENEMANAGER::HandleEvents(unsigned char key, bool press) {
	if (!CurScene) return;
	CurScene->HandleEvents(key, press);
}

void SCENEMANAGER::HandleEvents(int key, bool press) {
	if (!CurScene) return;
	CurScene->HandleEvents(key, press);
}

void SCENEMANAGER::HandleEvents(int button, int state, int x, int y) {
	if (!CurScene) return;
	CurScene->HandleEvents(button, state, x, y);
}


void SCENEMANAGER::Update()
{
	if (!CurScene) return;
	CurScene->Update();
}

void SCENEMANAGER::Render()
{
	if (!CurScene) return;
	CurScene->Render();
}

void SCENEMANAGER::SwitchScene(SCENEMANAGER::e_SceneType _type)
{
	if (CurScene)
	{
		delete CurScene;
		CurScene = nullptr;
	}

	switch (_type)
	{
	case e_SceneType::Logo:
		CurScene = new SCENELOGO;
		break;
	case e_SceneType::Menu:
		CurScene = new SCENEMENU;
		break;
	case e_SceneType::Game:
		CurScene = new SCENEGAME;
		break;
	}
}