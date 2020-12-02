#include "BackGround.h"

BACKGROUND::BACKGROUND() {
	ReadObj();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);

	std::random_device rd;
	std::mt19937_64 rnd(rd());
	std::uniform_real_distribution<float> uid(0, 1);
	float FirstCol[3] = { uid(rnd), uid(rnd), uid(rnd) };
	for (int i = 0; i < 3; ++i) {
		COL[i][0] = FirstCol[0];
		COL[i][1] = FirstCol[1];
		COL[i][2] = FirstCol[2];
	}
}

void BACKGROUND::Load(float* translate) {

	std::random_device rd;
	std::mt19937_64 rnd(rd());
	std::uniform_real_distribution<float> uid(-0.1, 0.1);

	BNODE* NewNode = new BNODE;
	NewNode->translate.x = translate[0];
	NewNode->translate.y = translate[1];
	NewNode->translate.z = translate[2];
	NewNode->MoveSpeed = uid(rnd);

	if (BGList == NULL) {
		BGList = NewNode;
	}
	else {
		BNODE* LastNode = BGList;
		while (LastNode->next != NULL) LastNode = LastNode->next;
		LastNode->next = NewNode;
	}
}

void BACKGROUND::ReadObj() {
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

	BGObj.Vertex = vertex;
	BGObj.Face = face;

	BGObj.VertexIndex = vertIndex;
	BGObj.FaceIndex = faceIndex;

	fclose(path);
}

void BACKGROUND::Render() {
	GET_SHADER->Activate(PROGRAM_BACKGROUND);
	GET_CAMERA->SetProjectionTransform(PROGRAM_BACKGROUND);
	GET_CAMERA->SetViewTransform(PROGRAM_BACKGROUND);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < BGObj.FaceIndex; ++i)
		DrawCube(BGObj.Face[i].x - 1, BGObj.Face[i].y - 1, BGObj.Face[i].z - 1);

	glDisable(GL_BLEND);
}

void BACKGROUND::DrawCube(int V1, int V2, int V3) {
	GLfloat POS[3][3] = {
		{BGObj.Vertex[V1].x, BGObj.Vertex[V1].y, BGObj.Vertex[V1].z},
		{BGObj.Vertex[V2].x, BGObj.Vertex[V2].y, BGObj.Vertex[V2].z},
		{BGObj.Vertex[V3].x, BGObj.Vertex[V3].y, BGObj.Vertex[V3].z}
	};

	{
		glm::mat4 scaling(1.0f);
		scaling = glm::scale(scaling, glm::vec3(1, 3, 1));
		glm::mat4 translating(1.0f);
		
		glm::mat4 result(1.0f);
		result = translating * scaling;

		unsigned int location = GET_SHADER->GetLocation("Model", PROGRAM_BACKGROUND);
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

void BACKGROUND::ChangeCol() {
	std::random_device rd;
	std::mt19937_64 rnd(rd());
	std::uniform_real_distribution<float> uid(0, 1);
	float NextCol[3] = { uid(rnd), uid(rnd), uid(rnd) };

	for (int i = 0; i < 3; ++i) {
		COL[i][0] = NextCol[0];
		COL[i][1] = NextCol[1];
		COL[i][2] = NextCol[2];
	}
}

void BACKGROUND::Update() {

}
