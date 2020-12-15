#pragma once
#include "Globals.h"
#include <random>
#define GET_PC PARTICLE::Instance()

struct PCUBE {
	glm::vec3* Vertex = NULL;
	glm::vec3* Face = NULL;
	int VertexIndex = 0;
	int FaceIndex = 0;
};

struct PNODE {
	glm::vec3 translate;
	float Gravity;
	float Movexz[2];
	PNODE* next;
};

class PARTICLE
{
public:
	PARTICLE();

	void ReadObj();

	void Load(float x, float z);

	void Render();

	void DrawCube(int V1, int V2, int V3, glm::vec3 translate, float C1, float C2, float C3);

	void Update();

	void ClearList();

	void ClearObj();

	bool NoParticle();

private:
	PCUBE PaticleObj;
	PNODE* PCList;
	GLuint VAO, VBO[2];
public:
	static PARTICLE* Instance() {
		static PARTICLE* ParticleInstance = nullptr;
		if (ParticleInstance == nullptr)
			ParticleInstance = new PARTICLE;

		return ParticleInstance;
	}
};

