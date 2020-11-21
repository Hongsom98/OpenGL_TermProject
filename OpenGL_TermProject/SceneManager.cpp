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
		CurScene = new SceneMenu;
		break;
	case e_SceneType::test:
		CurScene = new test;
		break;
	}
}