#pragma once

#include "Globals.h"
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
};

class TILE
{
public:
	void Load();

	void ReadObj();
	GLuint loadBMP(const char* imagepath);

	void Render();
	void DrawCube(int V1, int V2, int V3, int N1, int N2, int N3, int U1, int U2, int U3);
private:
	Tile TileObj;
	GLuint VAO, VBO[2];
	GLuint Texture[7];

public:
	static TILE* Instance() {
		static TILE* TileInstance = nullptr;
		if (TileInstance == nullptr)
			TileInstance = new TILE;

		return TileInstance;
	}
};

