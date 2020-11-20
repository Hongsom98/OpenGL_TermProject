#pragma once

#include "Shader.h"
#include "Camera.h"

enum CUBECOLOR { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };

struct CUBE {
	glm::vec3* Vertex = NULL;
	glm::vec3* Face = NULL;
	glm::vec3* UVDate = NULL;
	glm::vec2* UV = NULL;
	int VertexIndex = 0;
	int FaceIndex = 0;
	int UVIndex = 0;
};

class PLAYER
{
public:
	PLAYER()
	{
		result = glm::mat4(1.0f);
	}

	void Load();

	void ReadObj();
	GLuint loadBMP(const char* imagepath);

	void Render(SHADER& shader, CAMERA& camera);
	void DrawCube(int V1, int V2, int V3, int U1, int U2, int U3, SHADER& shader);
	void HandleEvents(unsigned char key, bool press);
	void SetPlayerRotateX(float);
	void SetPlayerRotateMX(float);
	void SetPlayerRotateZ(float);
	void SetPlayerRotateMZ(float);
	void GetPlayerKey(int key);
private:
	CUBE PlayerObj;
	GLuint VAO, VBO[2];
	GLuint Texture;
	float PlayerRotate[2] = { 0 }; // x, z
	int CubeAxis=0;

	glm::mat4 result;
};
