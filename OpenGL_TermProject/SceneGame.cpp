#include "SceneGame.h"

SCENEGAME::SCENEGAME()
{
	std::cout << "Scene Game" << std::endl;
	float testarr[3] = { 2, -1.05, 0 };
	GET_TILE->Load(1, testarr);
	testarr[0] = 0; testarr[1] = -1.05; testarr[2] = 0;
	GET_TILE->Load(0, testarr);
	testarr[0] = -2; testarr[1] = -1.05; testarr[2] = 0;
	GET_TILE->Load(2, testarr);
	testarr[0] = 0; testarr[1] = -1.05; testarr[2] = 2;
	GET_TILE->Load(3, testarr);
	testarr[0] = 0; testarr[1] = -1.05; testarr[2] = -2;
	GET_TILE->Load(4, testarr);
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
	GET_TILE->Render();
}

void SCENEGAME::TileGen() {

}