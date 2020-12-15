#pragma once
#include "Globals.h"
#define GET_BB BLACKBOX::Instance()

class BLACKBOX
{
public:
	BLACKBOX();

	void ReadObj();

	void Update();

	void Render();

	void DrawCube(int V1, int V2, int V3);

	void SetAlpha();

private:
	glm::vec3* Vertex;
	int VertexIndex;
	glm::vec3* Face;
	int FaceIndex;

	float alpha;
	GLuint VAO, VBO[2];
public:
	static BLACKBOX* Instance() {
		static BLACKBOX* BlackBoxInstance = nullptr;
		if (BlackBoxInstance == nullptr)
			BlackBoxInstance = new BLACKBOX;

		return BlackBoxInstance;
	}
};

