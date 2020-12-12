#pragma once

#include "Globals.h"
#include <random>
#define GET_BG BACKGROUND::Instance()


struct BCUBE {
	glm::vec3* Vertex = NULL;
	glm::vec3* Face = NULL;
	int VertexIndex = 0;
	int FaceIndex = 0;
};

struct BNODE {
	glm::vec3 translate;
	float MoveSpeed;
	int MoveCnt;
	BNODE* next = NULL;
};

class BACKGROUND
{
private:
	BCUBE BGObj;
	BNODE* BGList;
	GLuint VAO, VBO[2];
	GLfloat COL[3][3];
public:
	BACKGROUND();

	void Load(float* translate);

	void ReadObj();

	void Render();
	void DrawCube(int V1, int V2, int V3, glm::vec3 translate);
	void SetAlpha();

	void ChangeCol();

	void Update();
public:
	static BACKGROUND* Instance() {
		static BACKGROUND* BackGroundInstance = nullptr;
		if (BackGroundInstance == nullptr)
			BackGroundInstance = new BACKGROUND;

		return BackGroundInstance;
	}
};
