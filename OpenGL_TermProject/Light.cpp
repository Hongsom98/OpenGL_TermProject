#include "Light.h"

LIGHT::LIGHT() {
	LightPos.x = 0.0f;
	LightPos.y = 3.0f;
	LightPos.z = 0.0f;

	LightCol.r = 1.0f;
	LightCol.g = 1.0f;
	LightCol.b = 1.0f;
}

void LIGHT::Init() {

}

void LIGHT::SetLight(int ProgramID) {

	int lightPosLocation = GET_SHADER->GetLocation("lightPos", ProgramID); 
	glUniform3f(lightPosLocation, LightPos.x, LightPos.y, LightPos.z);

	int lightColorLocation = GET_SHADER->GetLocation("lightColor", ProgramID);
	glUniform3f(lightColorLocation, LightCol.r, LightCol.g, LightCol.b);

	int lightViewPosLocation = GET_SHADER->GetLocation("viewPos", ProgramID);
	glUniform3f(lightViewPosLocation, GET_CAMERA->GetCameraXPos(), GET_CAMERA->GetCameraYPos(), GET_CAMERA->GetCameraZPos());
}
