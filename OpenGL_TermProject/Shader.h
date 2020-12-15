#pragma once

#include "Globals.h"
#define GET_SHADER SHADER::Instance()
#pragma warning(disable:4996)

#define TOTALPROGRAMS 5

enum {
	PROGRAM_PLAYER,
	PROGRAM_BACKGROUND,
	PROGRAM_TILE,
	PROGRAM_FONT,
	PROGRAM_PARTICLE
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

public:
	static SHADER* Instance() {
		static SHADER* ShaderInstance = nullptr;
		if (ShaderInstance == nullptr)
			ShaderInstance = new SHADER;

		return ShaderInstance;
	}
};
