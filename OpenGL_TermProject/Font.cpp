#include "Font.h"

void FONT::Load() {
	ReadObj();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);

	Texture = loadBMP("bitmap_player.bmp");

	
}

void FONT::ReadObj() {
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

	if (FontObj.Vertex != NULL) {
		delete[] FontObj.Vertex;
		delete[] FontObj.Face;
		FontObj.Vertex = NULL;
		FontObj.Face = NULL;
		FontObj.UV = NULL;
		FontObj.UVData = NULL;
	}

	FontObj.Vertex = vertex;
	FontObj.Face = face;
	FontObj.UV = uv;
	FontObj.UVData = uvdata;
	FontObj.NormalData = normaldata;
	FontObj.Normal = normal;
	
	FontObj.VertexIndex = vertIndex;
	FontObj.FaceIndex = faceIndex;
	FontObj.UVIndex = uvIndex;
	FontObj.NormalIndex = normalIndex;

	fclose(path);
}

GLuint FONT::loadBMP(const char* imagepath) {
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
