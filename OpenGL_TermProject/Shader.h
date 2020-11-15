#pragma once

#include "Globals.h"
#pragma warning(disable:4996)

#define TOTALPROGRAMS 3

enum {
	PROGRAM_PLAYER,
	PROGRAM_BACKGROUND,
	PROGRAM_TILE
};

class SHADER
{
public:
	void Activate(int ProgramID);
	void Load();

	GLint GetLocation(const char* uniform, int ProgramID) { return glGetUniformLocation(programs[ProgramID], uniform); }

private:
	void InitShader();
	void MakeVertexShader(int ProgramID);
	void MakeFragmentShader(int ProgramID);

	GLchar* vertexsource, * fragmentsource;
	GLuint vertexshader, fragmentshader;
	GLuint programs[TOTALPROGRAMS];
	int CurrentProgramID;
};
