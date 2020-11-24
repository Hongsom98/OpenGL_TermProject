#pragma once

#include "Globals.h"

#define TIMER 100
#define ROTATEPERFRAME 90 / 10
#define GET_PLAYER PLAYER::Instance()

enum CUBECOLOR { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };
enum CUBESTATE { STAY, MOVEFORWARD, MOVEBACK, MOVELEFT, MOVERIGHT};


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
	PLAYER() {
		result = glm::mat4(1.0f);
	}

	void Load();

	void ReadObj();
	GLuint loadBMP(const char* imagepath);

	void Render();
	void DrawCube(int V1, int V2, int V3, int U1, int U2, int U3);
	void HandleEvents(unsigned char key, bool press);
	void PlayerMoveX(float);
	void PlayerMoveZ(float);

	void Update();
private:
	CUBE PlayerObj;
	GLuint VAO, VBO[2];
	GLuint Texture;
	float PlayerRotate[2] = { 0 }; // x, z
	int TargetRotate[2] = { 0 };
	glm::vec3 AxisForMove[4]; // ╩С, го, аб, ©Л
	CUBESTATE PlayerState = STAY;
	int CubeAxis=0;
	float A = 0.f;
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	glm::mat4 result;

public:
	static PLAYER* Instance() {
		static PLAYER* PlayeRInstance = nullptr;
		if (PlayeRInstance == nullptr)
			PlayeRInstance = new PLAYER;

		return PlayeRInstance;
	}
};
