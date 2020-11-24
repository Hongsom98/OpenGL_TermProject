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
				break;
			case VK_ESCAPE:
				glutLeaveMainLoop();
				break;
			case 'w':
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

}