#pragma once

#include "Shader.h"

class CAMERA
{
public:
	CAMERA();

	void Init();

	void SetViewTransform(SHADER* Shader, int ProgramID);
	
	void SetProjectionTransform(SHADER* Shader, int ProgramID);

	float GetCameraXPos() { return CameraPos.x; }

	float GetCameraYPos() { return CameraPos.y; }

	float GetCameraZPos() { return CameraPos.z; }
private:
	glm::vec3 CameraPos;
	glm::vec3 CameraDirection;
};
