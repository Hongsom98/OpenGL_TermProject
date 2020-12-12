#pragma once

#include "Globals.h"
#define GET_CAMERA CAMERA::Instance()

class CAMERA
{
public:
	CAMERA();

	void Init();

	void SetViewTransform(int ProgramID);
	
	void SetProjectionTransform(int ProgramID);

	void SetProjectionTransformForBG(int ProgramID);

	float GetCameraXPos() { return CameraPos.x; }

	float GetCameraYPos() { return CameraPos.y; }

	float GetCameraZPos() { return CameraPos.z; }
private:
	glm::vec3 CameraPos;
	glm::vec3 CameraDirection;

public:
	static CAMERA* Instance() {
		static CAMERA* CameraInstance = nullptr;
		if (CameraInstance == nullptr)
			CameraInstance = new CAMERA;

		return CameraInstance;
	}
};
