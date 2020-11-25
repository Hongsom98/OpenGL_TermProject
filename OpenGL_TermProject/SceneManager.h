#pragma once

#include "iScene.h"
#include "SceneLogo.h"
#include "SceneMenu.h"
#include "SceneGame.h"

#define GET_SCENEMANAGER SCENEMANAGER::Instance()

class SCENEMANAGER
{
public:
	enum class e_SceneType {
		Logo,
		Menu,
		Game
	};

public:
	SCENEMANAGER();
	~SCENEMANAGER();
	
	void Init();
	void HandleEvents(unsigned char key, bool press);
	void HandleEvents(int key, bool press);
	void HandleEvents(int button, int state, int x, int y);
	void Update();
	void Render();
	void SwitchScene(e_SceneType _type);

private:
	iScene* CurScene = nullptr;
public:
	static SCENEMANAGER* Instance() {
		static SCENEMANAGER* SceneManagerInstance = nullptr;
		if (SceneManagerInstance == nullptr)
			SceneManagerInstance = new SCENEMANAGER;

		return SceneManagerInstance;
	}

};
