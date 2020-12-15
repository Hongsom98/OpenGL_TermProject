#include "Shader.h"

char* filetobuf(const char* file) {
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;

	fseek(fptr, 0, SEEK_END);

	length = ftell(fptr);

	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);

	fread(buf, length, 1, fptr);

	fclose(fptr);

	buf[length] = 0;

	return buf;
}

void SHADER::Load() {
	InitShader();
}

void SHADER::Activate(int ProgramID) {
	glUseProgram(programs[ProgramID]);
	CurrentProgramID = ProgramID;
}

void SHADER::InitShader() {
	for (int i = 0; i < TOTALPROGRAMS; ++i) {
		MakeVertexShader(i);
		MakeFragmentShader(i);

		programs[i] = glCreateProgram();

		glAttachShader(programs[i], vertexshader);
		glAttachShader(programs[i], fragmentshader);

		glLinkProgram(programs[i]);

		glDeleteShader(vertexshader);
		glDeleteShader(fragmentshader);
	}
}

void SHADER::MakeVertexShader(int ProgramID) {
	switch (ProgramID) {
	case PROGRAM_PLAYER:
		vertexsource = filetobuf("Player.vert");
		break;
	case PROGRAM_BACKGROUND:
		vertexsource = filetobuf("BackGround.vert");
		break;
	case PROGRAM_TILE:
		vertexsource = filetobuf("Tile.vert");
		break;
	case PROGRAM_FONT:
		vertexsource = filetobuf("Font.vert");
		break;
	case PROGRAM_PARTICLE:
		vertexsource = filetobuf("Particle.vert");
		break;
	}

	vertexshader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);

	glCompileShader(vertexshader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
	else {
		std::cout << "Vertex Shader Compile Complete" << std::endl;
	}
}

void SHADER::MakeFragmentShader(int ProgramID) {
	switch (ProgramID) {
	case PROGRAM_PLAYER:
		fragmentsource = filetobuf("Player.frag");
		break;
	case PROGRAM_BACKGROUND:
		fragmentsource = filetobuf("BackGround.frag");
		break;
	case PROGRAM_TILE:
		fragmentsource = filetobuf("Tile.frag");
		break;
	case PROGRAM_FONT:
		fragmentsource = filetobuf("Font.frag");
		break;
	case PROGRAM_PARTICLE:
		fragmentsource = filetobuf("Particle.frag");
		break;
	}

	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);

	glCompileShader(fragmentshader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
	else {
		std::cout << "Fragmenet Shader Compile Complete" << std::endl;
	}
}
