#pragma once

#include "Globals.h"
#define GET_FONT FONT::Instance()

#define TOTALFONT 4

enum {
	FONT_UI,
	FONT_START,
	FONT_QUIT,
	FONT_VOLUME
};

struct Font {
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
class FONT
{
public:

	void	Load();

	void	ReadObj();
	GLuint	loadBMP(const char* imagepath);

private:
	Font FontObj;
	GLuint	VAO, VBO[2];
	GLuint	Texture;


public:
	static FONT* Instance() {
		static FONT* FontInstance= nullptr;
		if (FontInstance == nullptr)
			FontInstance = new FONT;

		return FontInstance;
	}
};

