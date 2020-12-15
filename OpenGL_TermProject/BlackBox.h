#pragma once
#include "Globals.h"
#define GET_BB BLACKBOX::Instance()

class BLACKBOX
{
public:

private:
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

