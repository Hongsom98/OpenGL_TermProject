#pragma once

#include "Globals.h"
#define GET_LIGHT LIGHT::Instance()

class LIGHT
{
public:
	LIGHT();

	void Init();

	void SetLight(int ProgramID);

private:
	glm::vec3 LightPos;
	glm::vec3 LightCol;

public:
	static LIGHT* Instance() {
		static LIGHT* LightInstance = nullptr;
		if (LightInstance == nullptr)
			LightInstance = new LIGHT;

		return LightInstance;
	}
};
