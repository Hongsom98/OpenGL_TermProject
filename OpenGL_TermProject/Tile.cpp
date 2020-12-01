#include "Tile.h"

TILE::TILE() {
	ReadObj();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(3, VBO);

	TileObj.Texture[0] = loadBMP("Default_Tile.bmp");
	TileObj.Texture[1] = loadBMP("Purple_Tile.bmp");
	TileObj.Texture[2] = loadBMP("Red_Tile.bmp");
	TileObj.Texture[3] = loadBMP("White_Tile.bmp");
	TileObj.Texture[4] = loadBMP("Green_Tile.bmp");
	TileObj.Texture[5] = loadBMP("Blue_Tile.bmp");
	TileObj.Texture[6] = loadBMP("Yellow_Tile.bmp");

	TileList = NULL;
	SpecialTileCnt = 0;
}

void TILE::Load(int type, float* translate, glm::vec2& Location) {

	NODE* NewNode = new NODE;
	NewNode->TexIndex = type;
	if (type != 0) SpecialTileCnt++;
	NewNode->Translate.x = translate[0];
	NewNode->Translate.y = translate[1];
	NewNode->Translate.z = translate[2];
	NewNode->Location = Location;

	if (TileList == NULL) {
		TileList = NewNode;
	}
	else {
		NODE* LastNode = TileList;
		while (LastNode->next != NULL) LastNode = LastNode->next;
		LastNode->next = NewNode;
	}

}

void TILE::ClearList() {
	NODE* DelNode = TileList;
	NODE* TempNode;
	TileList = NULL;

	while (true) {
		TempNode = DelNode->next;
		delete DelNode;
		if (TempNode == NULL) break;
		DelNode = TempNode;
	}
}

void TILE::ReadObj() {
	FILE* path = fopen("cube.obj", "r");

	char count[128];
	int vertexnum = 0;
	int facenum = 0;
	int normalnum = 0;
	int uvnum = 0;
	while (!feof(path)) {
		fscanf(path, "%s", count);
		if (count[0] == 'v' && count[1] == '\0') vertexnum++;
		else if (count[0] == 'f' && count[1] == '\0') facenum++;
		else if (count[0] == 'v' && count[1] == 'n' && count[2] == '\0') normalnum++;
		else if (count[0] == 'v' && count[1] == 't' && count[3] == '\0') uvnum++;
		memset(count, '\0', sizeof(count));
	}

	rewind(path);

	int vertIndex = 0;
	int faceIndex = 0;
	int normalIndex = 0;
	int uvIndex = 0;
	glm::vec3* vertex = new glm::vec3[vertexnum];
	glm::vec3* face = new glm::vec3[facenum];
	glm::vec3* normaldata = new glm::vec3[facenum];
	glm::vec3* normal = new glm::vec3[normalnum];
	glm::vec3* uvdata = new glm::vec3[facenum];
	glm::vec2* uv = new glm::vec2[uvnum];

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
			uvdata[faceIndex].x = temp_uv[0]; uvdata[faceIndex].y = temp_uv[1]; uvdata[faceIndex].z = temp_uv[2];
			faceIndex++;
		}
		else if (bind[0] == 'v' && bind[1] == 'n' && bind[2] == '\0') {
			fscanf(path, "%f %f %f\n", &normal[normalIndex].x, &normal[normalIndex].y, &normal[normalIndex].z);
			normalIndex++;
		}
		else if (bind[0] == 'v' && bind[1] == 't' && bind[2] == '\0') {
			fscanf(path, "%f %f\n", &uv[uvIndex].x, &uv[uvIndex].y);
			uvIndex++;
		}
	}

	if (TileObj.Vertex != NULL) {
		delete[] TileObj.Vertex;
		delete[] TileObj.Face;
		TileObj.Vertex = NULL;
		TileObj.Face = NULL;
		TileObj.UV = NULL;
		TileObj.UVData = NULL;
	}

	TileObj.Vertex = vertex;
	TileObj.Face = face;
	TileObj.UV = uv;
	TileObj.UVData = uvdata;
	TileObj.NormalData = normaldata;
	TileObj.Normal = normal;

	TileObj.VertexIndex = vertIndex;
	TileObj.FaceIndex = faceIndex;
	TileObj.UVIndex = uvIndex;
	TileObj.NormalIndex = normalIndex;

	fclose(path);
}

GLuint TILE::loadBMP(const char* imagepath) {
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;

	FILE* file = fopen(imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width * height * 3;
	if (dataPos == 0)      dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}

void TILE::Render() {
	GET_SHADER->Activate(PROGRAM_TILE);
	GET_CAMERA->SetProjectionTransform(PROGRAM_TILE);
	GET_CAMERA->SetViewTransform(PROGRAM_TILE);
	GET_LIGHT->SetLight(PROGRAM_TILE);

	NODE* DrawNode = TileList;
	while (DrawNode != NULL) {
		for (int i = 0; i < TileObj.FaceIndex; ++i)
			DrawCube(TileObj.Face[i].x - 1, TileObj.Face[i].y - 1, TileObj.Face[i].z - 1, TileObj.NormalData[i].x - 1, TileObj.NormalData[i].y - 1, TileObj.NormalData[i].z - 1, TileObj.UVData[i].x - 1, TileObj.UVData[i].y - 1, TileObj.UVData[i].z - 1, DrawNode->Translate, DrawNode->TexIndex);
		DrawNode = DrawNode->next;
	}
}

void TILE::DrawCube(int V1, int V2, int V3, int N1, int N2, int N3, int U1, int U2, int U3,
			  glm::vec3 translate, GLuint TexIndex) 
{
	GLfloat POS[3][3] = {
		{TileObj.Vertex[V1].x, TileObj.Vertex[V1].y, TileObj.Vertex[V1].z},
		{TileObj.Vertex[V2].x, TileObj.Vertex[V2].y, TileObj.Vertex[V2].z},
		{TileObj.Vertex[V3].x, TileObj.Vertex[V3].y, TileObj.Vertex[V3].z}
	};
	GLfloat NOR[3][3] = {
		{TileObj.Normal[N1].x, TileObj.Normal[N1].y, TileObj.Normal[N1].z},
		{TileObj.Normal[N2].x, TileObj.Normal[N2].y, TileObj.Normal[N2].z},
		{TileObj.Normal[N3].x, TileObj.Normal[N3].y, TileObj.Normal[N3].z}
	};
	GLfloat TEX[3][2] = {
		{TileObj.UV[U1].x, TileObj.UV[U1].y},
		{TileObj.UV[U2].x, TileObj.UV[U2].y},
		{TileObj.UV[U3].x, TileObj.UV[U3].y}
	};

	{
		glm::mat4 scaling(1.0f);
		scaling = glm::scale(scaling, glm::vec3(1, 0.05, 1));
		glm::mat4 translating(1.0f);
		translating = glm::translate(translating, translate);
		glm::mat4 result(1.0f);
		result = translating * scaling;

		unsigned int location = GET_SHADER->GetLocation("Model", PROGRAM_TILE);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(result));
	}

	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(POS), POS, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(NOR), NOR, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TEX), TEX, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
	}
	{
		glActiveTexture(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, TileObj.Texture[TexIndex]);
	}
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool TILE::Update() {
	NODE* SearchNode = TileList;

	while (SearchNode != NULL) {
		if (SearchNode->TexIndex != 0) {
			if (SearchNode->Location == GET_PLAYER->GetLoc() && SearchNode->TexIndex == GET_PLAYER->GetCol() + 1) {
				SearchNode->TexIndex = 0;
				SpecialTileCnt--;
				if (SpecialTileCnt == 0) return true;
			}
		}
		SearchNode = SearchNode->next;
	}
	return false;
}

bool TILE::NoTile(float x, float z) {
	NODE* SearchNode = TileList;

	while (SearchNode != NULL) {
		if (SearchNode->Location.x == x && SearchNode->Location.y == z) return false;
		else SearchNode = SearchNode->next;
	}

	return true;
}