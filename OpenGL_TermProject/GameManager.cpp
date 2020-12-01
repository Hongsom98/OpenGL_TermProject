#include "GameManager.h"

void GameManager::Init() {
	GET_SHADER->Load();
	GET_PLAYER->Load();

	GET_LIGHT->SetLight(PROGRAM_BACKGROUND);
	GET_LIGHT->SetLight(PROGRAM_TILE);

	GET_CAMERA->SetViewTransform(PROGRAM_PLAYER);
	GET_CAMERA->SetViewTransform(PROGRAM_BACKGROUND);
	GET_CAMERA->SetViewTransform(PROGRAM_TILE);

	GET_CAMERA->SetProjectionTransform(PROGRAM_PLAYER);
	GET_CAMERA->SetProjectionTransform(PROGRAM_BACKGROUND);
	GET_CAMERA->SetProjectionTransform(PROGRAM_TILE);

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GET_SCENEMANAGER->Render();
	
	glutSwapBuffers();
}

void GameManager::Update() {
	GET_SCENEMANAGER->Update();
}