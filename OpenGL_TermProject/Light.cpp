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

void LIGHT::SetLight(SHADER* Shader, int ProgramID, CAMERA* Camera) {

	int lightPosLocation = Shader->GetLocation("LightPos", ProgramID); 
	glUniform3f(lightPosLocation, LightPos.x, LightPos.y, LightPos.z);

	int lightColorLocation = Shader->GetLocation("LightColor", ProgramID);
	glUniform3f(lightColorLocation, LightCol.r, LightCol.g, LightCol.b);

	int lightViewPosLocation = Shader->GetLocation("ViewPos", ProgramID); 
	glUniform3f(lightViewPosLocation, Camera->GetCameraXPos(), Camera->GetCameraYPos(), Camera->GetCameraZPos());
}
