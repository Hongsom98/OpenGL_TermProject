#include "BlackBox.h"

BLACKBOX::BLACKBOX() {
	ReadObj();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);

	alpha = 0.0;
	BB_OnOff = false;
}

void BLACKBOX::ReadObj() {
	FILE* path = fopen("cube.obj", "r");

	char count[128];
	int vertexnum = 0;
	int facenum = 0;
	while (!feof(path)) {
		fscanf(path, "%s", count);
		if (count[0] == 'v' && count[1] == '\0') vertexnum++;
		else if (count[0] == 'f' && count[1] == '\0') facenum++;
		memset(count, '\0', sizeof(count));
	}
	rewind(path);

	int vertIndex = 0;
	int faceIndex = 0;
	glm::vec3* vertex = new glm::vec3[vertexnum];
	glm::vec3* face = new glm::vec3[facenum];

	char bind[128];

	while (!feof(path)) {
		fscanf(path, "%s", bind);

		if (bind[0] == 'v' && bind[1] == '\0') {
			fscanf(path, "%f %f %f\n", &vertex[vertIndex].x, &vertex[vertIndex].y, &vertex[vertIndex].z);
			vertIndex++;
		}
		else if (bind[0] == 'f' && bind[1] == '\0') {
			unsigned int temp_face[3], temp_uv[3], temp_normal[3];
			fscanf(path, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &temp_face[0], &temp_uv[0], &temp_normal[0], &temp_face[1], &temp_uv[1], &temp_normal[1], &temp_face[2], &temp_uv[2], &temp_normal[2]);
			face[faceIndex].x = temp_face[0]; face[faceIndex].y = temp_face[1]; face[faceIndex].z = temp_face[2];
			faceIndex++;
		}
	}

	Vertex = vertex;
	Face = face;

	VertexIndex = vertIndex;
	FaceIndex = faceIndex;

	fclose(path);
}

void BLACKBOX::Update() {
	if (BB_OnOff) {
		alpha += DELTATIME * 0.02;
		if (alpha >= 1.0) {
			alpha = 1.0;
			BB_OnOff = false;
		}
	}
	else {
		if (alpha <= 0) return;
		alpha -= DELTATIME * 0.01;
		if (alpha <= 0) alpha = 0.0;
	}
}

void BLACKBOX::Render() {
	GET_SHADER->Activate(PROGRAM_BLACKBOX);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetAlpha();

	for (int i = 0; i < FaceIndex; ++i)
		DrawCube(Face[i].x - 1, Face[i].y - 1, Face[i].z - 1);
}

void BLACKBOX::DrawCube(int V1, int V2, int V3) {
	GLfloat POS[3][3] = {
		{Vertex[V1].x, Vertex[V1].y, Vertex[V1].z},
		{Vertex[V2].x, Vertex[V2].y, Vertex[V2].z},
		{Vertex[V3].x, Vertex[V3].y, Vertex[V3].z}
	};
	GLfloat COL[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};

	{
		glm::mat4 scaling(1.0f);
		scaling = glm::scale(scaling, glm::vec3(1, 1, 1));
		glm::mat4 result(1.0f);
		result = scaling;

		unsigned int location = GET_SHADER->GetLocation("Model", PROGRAM_BLACKBOX);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(result));
	}

	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(POS), POS, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(COL), COL, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void BLACKBOX::SetAlpha() {
	unsigned int location = GET_SHADER->GetLocation("Alpha", PROGRAM_BLACKBOX);
	glUniform1f(location, alpha);
}

void BLACKBOX::BB_ON() {
	BB_OnOff = true;
}

float BLACKBOX::GetAlpha() {
	return alpha;
}