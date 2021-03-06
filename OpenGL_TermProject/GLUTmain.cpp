
#include "GameManager.h"

void Reshape(int w, int h) {
	GameManager::Instance()->Reshape(w, h);
}

void Render() {
	GameManager::Instance()->Render();
}

void Keyboard(unsigned char key, int x, int y) {
	GameManager::Instance()->ReadKeyboard(key, x, y, true);
}

void KeyboardUp(unsigned char key, int x, int y) {
	GameManager::Instance()->ReadKeyboard(key, x, y, false);
}

void SpecialKeyboard(int key, int x, int y) {
	GameManager::Instance()->ReadSpecialKeyboard(key, x, y, true);
}

void SpecialKeyboardUp(int key, int x, int y) {
	GameManager::Instance()->ReadSpecialKeyboard(key, x, y, false);
}

void Mouse(int button, int state, int x, int y) {
	GameManager::Instance()->ReadMouse(button, state, x, y);
}

void MouseMotion(int x, int y) {
	GameManager::Instance()->ReadMouseMotion(x, y);
}

void Update(int val) {
	GameManager::Instance()->Update();

	glutPostRedisplay();
	glutTimerFunc(50, Update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	int res_x = glutGet(GLUT_SCREEN_WIDTH);
	int res_y = glutGet(GLUT_SCREEN_HEIGHT);
	int pos_x = (res_x >> 1) - (SCREEN_WIDTH >> 1);
	int pos_y = (res_y >> 1) - (SCREEN_HEIGHT >> 1);
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(pos_x, pos_y);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("SoloveCube");

	HWND hWndConsole = GetConsoleWindow();
	ShowWindow(hWndConsole, SW_HIDE);



	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW Initialized\n";

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(SpecialKeyboard);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutTimerFunc(1, Update, 0);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GameManager::Instance()->Init();

	glutMainLoop();
}
