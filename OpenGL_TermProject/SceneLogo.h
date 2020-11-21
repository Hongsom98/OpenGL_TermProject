#pragma once
#include "Globals.h"
#include "iScene.h"

class SCENELOGO :
	public iScene
{
private:
	int Aninum;
	float Delttime;
public:
	SCENELOGO();
	~SCENELOGO();

	void Init();
	void Update();
	void Render();
	void Destroy();
};

