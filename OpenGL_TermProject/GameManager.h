#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Light.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800

class GameManager {
public:
	void Init();

	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	
	void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);
	
	void ReadMouse(int button, int state, int x, int y);
	
	void ReadMouseMotion(int x, int y);
	
	void Reshape(int w, int h);

	void Render();

private:
	SHADER Shader;
	CAMERA Camera;
	LIGHT Light;
};
