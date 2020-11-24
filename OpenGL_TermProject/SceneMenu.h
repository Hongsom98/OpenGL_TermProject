#pragma once
#include "Globals.h"

class SCENEMENU :
	public iScene
{
private:

public:
	SCENEMENU();
	~SCENEMENU();

	void Init();
	void HandleEvents(unsigned char key, bool press);
	void HandleEvents(int key, bool press);
	void HandleEvents(int button, int state, int x, int y);
	void Update();
	void Render();
};
