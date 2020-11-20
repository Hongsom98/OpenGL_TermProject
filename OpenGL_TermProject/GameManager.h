#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Player.h"
#include "Sound.h"

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

	void Update();

private:
	SHADER Shader;
	CAMERA Camera;
	LIGHT Light;
	PLAYER Player;

public:
	static GameManager* Instance() {
		static GameManager* GameManagerInstance = nullptr;
		if (GameManagerInstance == nullptr)
			GameManagerInstance = new GameManager;

		return GameManagerInstance;
	}
};
