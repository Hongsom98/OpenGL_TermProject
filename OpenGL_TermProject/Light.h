#pragma once

#include "Shader.h"
#include "Camera.h"

class LIGHT
{
public:
	LIGHT();

	void Init();

	void SetLight(SHADER* Shader, int ProgramID, CAMERA* Camera);

private:
	glm::vec3 LightPos;
	glm::vec3 LightCol;
};
