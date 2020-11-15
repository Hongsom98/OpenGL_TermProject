#include "GameManager.h"

void GameManager::Init() {
	Shader.Load();
}

void GameManager::ReadKeyboard(unsigned char key, int x, int y, bool press) {

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

	glutSwapBuffers();
}
