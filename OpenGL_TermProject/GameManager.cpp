#include "GameManager.h"

void GameManager::Init() {
	Shader.Load();
	Player.Load();

	Light.SetLight(Shader, PROGRAM_BACKGROUND, Camera);
	Light.SetLight(Shader, PROGRAM_TILE, Camera);

	Camera.SetViewTransform(Shader, PROGRAM_PLAYER);
	Camera.SetViewTransform(Shader, PROGRAM_BACKGROUND);
	Camera.SetViewTransform(Shader, PROGRAM_TILE);

	Camera.SetProjectionTransform(Shader, PROGRAM_PLAYER);
	Camera.SetProjectionTransform(Shader, PROGRAM_BACKGROUND);
	Camera.SetProjectionTransform(Shader, PROGRAM_TILE);
}

void GameManager::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	if(press)
	switch (key)
	{
		case 'q':
		case 'Q':
			glutLeaveMainLoop();
			break;
		case 'w':
		case 's':
		case 'a':
		case 'd':
			Player.HandleEvents(key, press);
			break;
	}
}

void GameManager::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) {

}

void GameManager::ReadMouse(int button, int state, int x, int y) {

}

void GameManager::ReadMouseMotion(int x, int y) {

}

void GameManager::Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void GameManager::Render() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Player.Render(Shader, Camera);
	
	glutSwapBuffers();
}

void GameManager::Update() {
	Player.Update();
}