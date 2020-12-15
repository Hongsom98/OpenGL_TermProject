#include "Particle.h"

PARTICLE::PARTICLE() {
	ReadObj();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);

	PCList = NULL;
}

void PARTICLE::ReadObj() {
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

	PaticleObj.Vertex = vertex;
	PaticleObj.Face = face;

	PaticleObj.VertexIndex = vertIndex;
	PaticleObj.FaceIndex = faceIndex;

	fclose(path);
}

void PARTICLE::Load(float x, float z) {

	std::random_device rd;
	std::mt19937_64 rnd(rd());
	std::uniform_real_distribution<float> yuid(0, 1.0);
	std::uniform_real_distribution<float> xzuid(-1.0, 1.0);
	std::uniform_int_distribution<int> numuid(10, 20);

	for (int i = 0; i < numuid(rnd); ++i) {
		PNODE* NewNode = new PNODE;
		NewNode->translate.x = x + xzuid(rnd);
		NewNode->translate.y = 1;
		NewNode->translate.z = z + xzuid(rnd);
		
		NewNode->Movexz[0] = xzuid(rnd) * 0.5;
		NewNode->Movexz[1] = xzuid(rnd) * 0.5;

		NewNode->Gravity = yuid(rnd);
		NewNode->next = NULL;

		if (PCList == NULL) {
			PCList = NewNode;
		}
		else {
			PNODE* LastNode = PCList;
			while (LastNode->next != NULL) LastNode = LastNode->next;
			LastNode->next = NewNode;
		}
	}
}

void PARTICLE::Render() {
	GET_SHADER->Activate(PROGRAM_PARTICLE);
	GET_CAMERA->SetProjectionTransform(PROGRAM_PARTICLE);
	GET_CAMERA->SetViewTransform(PROGRAM_PARTICLE);

	PNODE* RenderNode = PCList;

	while (RenderNode != NULL) {
		std::random_device rd;
		std::mt19937_64 rnd(rd());
		std::uniform_real_distribution<float> uid(0, 1.0);
		float C1 = uid(rnd);
		float C2 = uid(rnd);
		float C3 = uid(rnd);
		if (!(RenderNode->translate.y <= -4)) {
			for (int i = 0; i < PaticleObj.FaceIndex; ++i)
				DrawCube(PaticleObj.Face[i].x - 1, PaticleObj.Face[i].y - 1, PaticleObj.Face[i].z - 1, RenderNode->translate, C1, C2, C3);
		}
		RenderNode = RenderNode->next;
	}

}

void PARTICLE::DrawCube(int V1, int V2, int V3, glm::vec3 translate, float C1, float C2, float C3) {
	GLfloat POS[3][3] = {
		{PaticleObj.Vertex[V1].x, PaticleObj.Vertex[V1].y, PaticleObj.Vertex[V1].z},
		{PaticleObj.Vertex[V2].x, PaticleObj.Vertex[V2].y, PaticleObj.Vertex[V2].z},
		{PaticleObj.Vertex[V3].x, PaticleObj.Vertex[V3].y, PaticleObj.Vertex[V3].z}
	};
	GLfloat COL[3][3] = {
		{C1, C2, C3},
		{C1, C2, C3},
		{C1, C2, C3}
	};

	{
		glm::mat4 scaling(1.0f);
		scaling = glm::scale(scaling, glm::vec3(0.2, 0.2, 0.2));
		glm::mat4 translating(1.0f);
		translating = glm::translate(translating, translate);
		glm::mat4 result(1.0f);
		result = translating * scaling;

		unsigned int location = GET_SHADER->GetLocation("Model", PROGRAM_PARTICLE);
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

void PARTICLE::Update() {
	PNODE* UpdateNode = PCList;

	while (UpdateNode != NULL) {
		UpdateNode->translate.y += UpdateNode->Gravity * 0.01;
		UpdateNode->translate.x += UpdateNode->Movexz[0];
		UpdateNode->translate.z += UpdateNode->Movexz[1];

		UpdateNode->Gravity -= DELTATIME;

		UpdateNode = UpdateNode->next;
	}
}

void PARTICLE::ClearList() {
	if (PCList == NULL) return;
	PNODE* DelNode = PCList;
	PNODE* TempNode;
	PCList = NULL;

	while (true) {
		TempNode = DelNode->next;
		delete DelNode;
		if (TempNode == NULL) break;
		DelNode = TempNode;
	}
}

void PARTICLE::ClearObj() {
	PNODE* DelNode = PCList;
	PNODE* TempNode;

	while (true) {
		TempNode = DelNode->next;
		if (DelNode->translate.y <= -5) {
			if (DelNode == PCList) PCList = PCList->next;
			delete DelNode;
		}
		if (TempNode == NULL) break;
		DelNode = TempNode;
	}
}

bool PARTICLE::NoParticle() {
	if (PCList == NULL) return true;
	else return false;
}
