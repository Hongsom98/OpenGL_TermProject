#include "Camera.h"


CAMERA::CAMERA() {
	CameraPos.x = 10.0f;
	CameraPos.y = 10.0f;
	CameraPos.z = 10.0f;

	CameraDirection.x = 0.0f;
	CameraDirection.y = 0.0f;
	CameraDirection.z = 0.0f;
}

void CAMERA::Init() {

}

void CAMERA::SetViewTransform(int ProgramID) {
	glm::vec3 cameraUp		  = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view			  = glm::lookAt(CameraPos, CameraDirection, cameraUp);

	unsigned int viewLocation = GET_SHADER->GetLocation("View", ProgramID);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}

void CAMERA::SetProjectionTransform(int ProgramID) {
	glm::mat4 projection     = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);

	unsigned int projectionLocation = GET_SHADER->GetLocation("Projection", ProgramID);

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void CAMERA::SetProjectionTransformForBG(int ProgramID) {
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);

	unsigned int projectionLocation = GET_SHADER->GetLocation("Projection", ProgramID);

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}
