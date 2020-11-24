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

	GET_SCENEMANAGER->Init();
}

void GameManager::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	if(press)
		switch (key)
		{
			case 'q':
			case 'Q':
				glutLeaveMainLoop();
				break;
			default:
				GET_SCENEMANAGER->HandleEvents(key, press);
		}
}

void GameManager::ReadSpecialKeyboard(int key, int x, int y, bool press) {
	if (press)
		GET_SCENEMANAGER->HandleEvents(key, press);
}

void GameManager::ReadMouse(int button, int state, int x, int y) {
	GET_SCENEMANAGER->HandleEvents(button, state, x, y);
}

void GameManager::ReadMouseMotion(int x, int y) {
	
}

void GameManager::Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void GameManager::Render() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GET_SCENEMANAGER->Render();
	
	glutSwapBuffers();
}

void GameManager::Update() {
	GET_SCENEMANAGER->Update();
}