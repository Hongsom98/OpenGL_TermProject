#include "SCENELOGO.h"

SCENELOGO::SCENELOGO()
{
	GET_TIMEMANAGER->SetPreTime();
}

SCENELOGO::~SCENELOGO()
{

}

void SCENELOGO::Init()
{

}

void SCENELOGO::HandleEvents(unsigned char key, bool press) 
{
	return;
}

void SCENELOGO::HandleEvents(int key, bool press)
{
	return;
}

void SCENELOGO::HandleEvents(int button, int state, int x, int y)
{
	return;
}

void SCENELOGO::Update()
{
	GET_TIMEMANAGER->SetCurTime();
	GET_TIMEMANAGER->CalDeltaTime();
	if (DELTATIME > 2.0) GET_SCENEMANAGER->SwitchScene(SCENEMANAGER::e_SceneType::Menu);
}

void SCENELOGO::Render()
{
	
}