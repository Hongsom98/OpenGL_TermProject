#pragma once

#include "SceneGame.h"
#define GET_TILE TILE::Instance()

struct Tile {
	glm::vec3* Vertex = NULL;
	glm::vec3* Face = NULL;
	glm::vec3* NormalData = NULL;
	glm::vec3* Normal = NULL;
	glm::vec3* UVData = NULL;
	glm::vec2* UV = NULL;
	int VertexIndex = 0;
	int FaceIndex = 0;
	int NormalIndex = 0;
	int UVIndex = 0;
	GLuint Texture[7];
};

struct NODE {
	glm::vec3 Translate;
	GLuint TexIndex;
	NODE* next = NULL;
};

class TILE
{
public:
	TILE();

	void Load(int type, float* translate);

	void ReadObj();
	GLuint loadBMP(const char* imagepath);

	void Render();
	void DrawCube(int V1, int V2, int V3, int N1, int N2, int N3, int U1, int U2, int U3,
				  glm::vec3 translate, GLuint TexIndex);
	void ClearList();

private:
	Tile TileObj;
	GLuint VAO, VBO[3];
	NODE* TileList;

public:
	static TILE* Instance() {
		static TILE* TileInstance = nullptr;
		if (TileInstance == nullptr)
			TileInstance = new TILE;

		return TileInstance;
	}
};

