#pragma once
#include "Globals.h"

class SCENEGAME :
    public iScene
{
private:
	//TILE test;
public:
	SCENEGAME();
	~SCENEGAME();

	void Init();
	void HandleEvents(unsigned char key, bool press);
	void HandleEvents(int key, bool press);
	void HandleEvents(int button, int state, int x, int y);
	void Update();
	void Render();

	void TileGen(const char* StagePath);
};
