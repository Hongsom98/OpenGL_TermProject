#include "Player.h"

void PLAYER::Load() {
	ReadObj();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
}

void PLAYER::ReadObj() {
	FILE* path = fopen("cube.obj", "r");
	
	char count[128];
	int vertexnum = 0;
	int facenum = 0;
	int normalnum = 0;
	while (!feof(path)) {
		fscanf(path, "%s", count);
		if (count[0] == 'v' && count[1] == '\0') vertexnum++;
		else if (count[0] == 'f' && count[1] == '\0') facenum++;
		else if (count[0] == 'v' && count[1] == 'n' && count[2] == '\0') normalnum++;
		memset(count, '\0', sizeof(count));
	}
	rewind(path);

	int vertIndex = 0;
	int faceIndex = 0;
	int normalIndex = 0;
	glm::vec3* vertex = new glm::vec3[vertexnum];
	glm::vec3* face = new glm::vec3[facenum];
	glm::vec3* normaldata = new glm::vec3[facenum];
	glm::vec3* normal = new glm::vec3[normalnum];

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
			normaldata[faceIndex].x = temp_normal[0]; normaldata[faceIndex].y = temp_normal[1]; normaldata[faceIndex].z = temp_normal[2];
			faceIndex++;
		}
		else if (bind[0] == 'v' && bind[1] == 'n' && bind[2] == '\0') {
			fscanf(path, "%f %f %f\n", &normal[normalIndex].x, &normal[normalIndex].y, &normal[normalIndex].z);
			normalIndex++;
		}
	}

	if (PlayerObj.Vertex != NULL) {
		delete[] PlayerObj.Vertex;
		delete[] PlayerObj.Face;
		PlayerObj.Vertex = NULL;
		PlayerObj.Face = NULL;
	}

	PlayerObj.Vertex = vertex;
	PlayerObj.Face = face;

	PlayerObj.VertexIndex = vertIndex;
	PlayerObj.FaceIndex = faceIndex;

	fclose(path);
}

void PLAYER::Render(SHADER* shader) {
	for (int i = 0; i < PlayerObj.FaceIndex; ++i)
		DrawCube(PlayerObj.Face[i].x - 1, PlayerObj.Face[i].y - 1, PlayerObj.Face[i].z - 1, shader);
}

void PLAYER::DrawCube(int V1, int V2, int V3, SHADER* shader) {
	GLfloat POS[3][3] = {
		{PlayerObj.Vertex[V1].x, PlayerObj.Vertex[V1].y, PlayerObj.Vertex[V1].z},
		{PlayerObj.Vertex[V2].x, PlayerObj.Vertex[V2].y, PlayerObj.Vertex[V2].z},
		{PlayerObj.Vertex[V3].x, PlayerObj.Vertex[V3].y, PlayerObj.Vertex[V3].z}
	};

	shader->Activate(PROGRAM_PLAYER);
	{
		glm::mat4 Xrotate = glm::rotate(Xrotate, glm::radians(PlayerRotate[0]), glm::vec3(1, 0, 0));
		glm::mat4 Zrotate = glm::rotate(Zrotate, glm::radians(PlayerRotate[1]), glm::vec3(0, 0, 1));
		glm::mat4 result = Zrotate * Xrotate;

		unsigned int location = shader->GetLocation("Model", PROGRAM_PLAYER);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(result));
	}
	{
		glm::vec3 Col(1, 0, 0);

		unsigned int location = shader->GetLocation("in_Color", PROGRAM_PLAYER);
		glUniform3f(location, Col.r, Col.g, Col.b);
	}
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(POS), POS, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void PLAYER::HandleEvents(unsigned char key, bool press) {

}