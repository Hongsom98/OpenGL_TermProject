#include "SCENEMENU.h"

SCENEMENU::SCENEMENU()
{
	std::cout << "Scene Menu" << std::endl;

}

SCENEMENU::~SCENEMENU()
{

}

void SCENEMENU::Init()
{

}

void SCENEMENU::HandleEvents(unsigned char key, bool press) 
{
	if(press)
		switch (key) {
			case VK_RETURN:
				GET_SCENEMANAGER->SwitchScene(SCENEMANAGER::e_SceneType::Game);
				GET_FONT->FontOut();
				GET_SOUND->PlayerDeath();
				GET_FONT->FontIn();
				GET_FONT->Status = FONT_PAUSE;
				break;
			case VK_ESCAPE:
				glutLeaveMainLoop();
				break;
			case 'w':
				GET_FONT->RotateRadian();
				break;
			case 's':
				break;
			case 'a':
				break;
			case 'd':
				break;
		}
}

void SCENEMENU::HandleEvents(int key, bool press)
{
	if(press)
		switch (key) {
			case GLUT_KEY_UP:
				break;
			case GLUT_KEY_DOWN:
				break;
			case GLUT_KEY_LEFT:
				break;
			case GLUT_KEY_RIGHT:
				break;
		}
}

void SCENEMENU::HandleEvents(int button, int state, int x, int y)
{

}

void SCENEMENU::Update()
{

}

void SCENEMENU::Render()
{
	GET_FONT->Render();
	
}