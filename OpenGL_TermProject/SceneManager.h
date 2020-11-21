#pragma once

#include "iScene.h"
#include "SceneLogo.h"

#define GET_SCENEMANAGER SceneManager::Instance()

class SCENEMANAGER
{
public:
	enum class e_SceneType {
		Logo,
		Menu,
		test
	};

public:
	SCENEMANAGER();
	~SCENEMANAGER();
	
	void Init();
	void Update();
	void Render();
	void SwitchScene(e_SceneType _type);

private:
	iScene* CurScene = nullptr;
	int PlayerMoney;
	bool Shotready;
	bool Waveready;
public:
	static SCENEMANAGER* Instance() {
		static SCENEMANAGER* SceneManagerInstance = nullptr;
		if (SceneManagerInstance == nullptr)
			SceneManagerInstance = new SCENEMANAGER;

		return SceneManagerInstance;
	}

};
