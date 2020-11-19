#pragma once

#include "Shader.h"
#include "Camera.h"

enum CUBECOLOR { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };

struct CUBE {
	glm::vec3* Vertex = NULL;
	glm::vec3* Face = NULL;
	int VertexIndex = 0;
	int FaceIndex = 0;
};

class PLAYER
{
public:
	void Load();

	void ReadObj();

	void Render(SHADER& shader, CAMERA& camera);
	void DrawCube(int V1, int V2, int V3, SHADER& shader);

	void HandleEvents(unsigned char key, bool press);

private:
	CUBE PlayerObj;
	GLuint VAO, VBO;
	float PlayerRotate[2] = { 0 }; // x, z
};
