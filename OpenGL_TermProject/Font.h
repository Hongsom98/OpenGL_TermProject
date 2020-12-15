#pragma once

#include "Globals.h"
#define GET_FONT FONT::Instance()

#define TOTALFONT 4

enum {
	FONT_START,
	FONT_RESTART,
	FONT_RESUME,
	FONT_PAUSE,
	FONT_VICTORY
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
	GLuint Status;
	void	Render();
	void	RenderUI();
	void	RenderUIPause();
	void	RenderVictory();
	void	Draw(int V1, int V2, int V3, int U1, int U2, int U3);
	void	DrawFont(int V1, int V2, int V3, int U1, int U2, int U3, glm::mat4,int eNum);
	void	FontOut();
	void	FontIn();
	void	FontPause();
	void	FontVictory();
	void	RotateRadian();

private:
	Font FontObj;
	
	GLuint	VAO, VBO[2];
	GLuint	Texture;
	GLuint	TextureUiPause;
	GLuint	TextureUiRestart;
	GLuint	TextureUiResume;
	GLuint	TextureUiVictory;
	glm::vec3 TransInfo;
	glm::mat4 result;
	glm::mat4 result1;
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

