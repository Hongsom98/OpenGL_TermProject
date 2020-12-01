#pragma once
#include "Globals.h"

class SCENEGAME :
    public iScene
{
private:
	int StageNum;
public:
	SCENEGAME();
	~SCENEGAME();

	void Init();
	void HandleEvents(unsigned char key, bool press);
	void HandleEvents(int key, bool press);
	void HandleEvents(int button, int state, int x, int y);
	void Update();
	void Render();

	void SwitchStage();
	void TileGen(const char* StagePath);
};
