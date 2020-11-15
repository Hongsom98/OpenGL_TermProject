#include "Camera.h"


CAMERA::CAMERA() {
	CameraPos.x = 1.0f;
	CameraPos.y = 1.0f;
	CameraPos.z = 1.0f;

	CameraDirection.x = 0.0f;
	CameraDirection.y = 0.0f;
	CameraDirection.z = 0.0f;
}

void CAMERA::Init() {

}

void CAMERA::SetViewTransform(SHADER* Shader, int ProgramID) {
	glm::vec3 cameraUp		  = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view			  = glm::lookAt(CameraPos, CameraDirection, cameraUp);

	unsigned int viewLocation = Shader->GetLocation("ViewTransform", ProgramID);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}

void CAMERA::SetProjectionTransform(SHADER* Shader, int ProgramID) {
	glm::mat4 projection     = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);

	unsigned int projectionLocation = Shader->GetLocation("ProjectionTransform", ProgramID);

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}
