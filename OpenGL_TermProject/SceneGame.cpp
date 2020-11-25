#include "SceneGame.h"

SCENEGAME::SCENEGAME()
{
	std::cout << "Scene Game" << std::endl;
}

SCENEGAME::~SCENEGAME()
{

}

void SCENEGAME::Init()
{

}

void SCENEGAME::HandleEvents(unsigned char key, bool press)
{
	if (press)
		switch (key) {
		case VK_RETURN:
			break;
		case VK_ESCAPE:
			glutLeaveMainLoop();
			break;
		case 'w':
		case 's':
		case 'a':
		case 'd':
			GET_PLAYER->HandleEvents(key, press);
			break;
		}
}

void SCENEGAME::HandleEvents(int key, bool press)
{
	if (press)
		switch (key) {
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			GET_PLAYER->HandleEvents(key, press);
			break;
		}
}

void SCENEGAME::HandleEvents(int button, int state, int x, int y)
{

}

void SCENEGAME::Update()
{
	GET_PLAYER->Update();
}

void SCENEGAME::Render()
{
	GET_PLAYER->Render();
}