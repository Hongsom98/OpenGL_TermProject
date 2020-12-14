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
	glm::vec3* UVData = NULL;
	glm::vec2* UV = NULL;
	int VertexIndex = 0;
	int FaceIndex = 0;
	int UVIndex = 0;
	
};
class FONT
{
public:
	void	Load();

	void	ReadObj();
	GLuint	loadBMP(const char* imagepath);
	
	void	Render();
	void	Draw(int V1, int V2, int V3, int U1, int U2, int U3);
	void	FontOut();
	void	RotateRadian();
private:
	Font FontObj;
	GLuint	VAO, VBO[2];
	GLuint	Texture;
	glm::vec3 TransInfo;
	glm::mat4 result;
	glm::vec3 TransFont;
	float Radian;
public:
	static FONT* Instance() {
		static FONT* FontInstance= nullptr;
		if (FontInstance == nullptr)
			FontInstance = new FONT;

		return FontInstance;
	}
};

