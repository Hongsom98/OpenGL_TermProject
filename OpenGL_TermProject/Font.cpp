#include "Font.h"

void FONT::Load() {
	ReadObj();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);

	Texture = loadBMP("Game_Start.bmp");
	TextureUiPause = loadBMP("UI_pause.bmp");
	TextureUiRestart = loadBMP("UI_restart.bmp");
	TextureUiResume = loadBMP("UI_resume.bmp");
	result = glm::mat4(1.0f);
	TransInfo = glm::vec3(0.f);
	TransFont = glm::vec3(0.f);
	Radian = 0;
	Status = 0;
}

void FONT::Render() {
	GET_SHADER->Activate(PROGRAM_FONT);
	
	Radian += 1;
	if (Radian == 360) Radian = 0;
	result = glm::translate(glm::mat4(1.0f),TransFont) * glm::rotate(glm::mat4(1.0f), glm::radians(Radian), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f),glm::vec3(0.7f,0.7f,0.7f));
	for (int i = 0; i < FontObj.FaceIndex; ++i)
		Draw(FontObj.Face[i].x - 1, FontObj.Face[i].y - 1, FontObj.Face[i].z - 1, FontObj.UVData[i].x - 1, FontObj.UVData[i].y - 1, FontObj.UVData[i].z - 1);
	
}

void FONT::RenderUI() {

	GET_SHADER->Activate(PROGRAM_FONT);

	result = glm::translate(glm::mat4(1.0f), TransFont) * glm::rotate(glm::mat4(1.0f), glm::radians(180.f), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.2f, 0.2f));
	
	for (int i = 0; i < FontObj.FaceIndex; ++i)
		Draw(FontObj.Face[i].x - 1, FontObj.Face[i].y - 1, FontObj.Face[i].z - 1, FontObj.UVData[i].x - 1, FontObj.UVData[i].y - 1, FontObj.UVData[i].z - 1);

}
void FONT::RenderUIPause() {

	GET_SHADER->Activate(PROGRAM_FONT);

	result = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0.5f, 0)) * glm::translate(glm::mat4(1.0f), TransFont) * glm::rotate(glm::mat4(1.0f), glm::radians(180.f), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f));
	result1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.5f, 0)) * glm::translate(glm::mat4(1.0f), TransFont) * glm::rotate(glm::mat4(1.0f), glm::radians(180.f), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f));
	for (int i = 0; i < FontObj.FaceIndex; ++i)
		DrawFont(FontObj.Face[i].x - 1, FontObj.Face[i].y - 1, FontObj.Face[i].z - 1, FontObj.UVData[i].x - 1, FontObj.UVData[i].y - 1, FontObj.UVData[i].z - 1,result, FONT_RESUME);
	for (int i = 0; i < FontObj.FaceIndex; ++i)
		DrawFont(FontObj.Face[i].x - 1, FontObj.Face[i].y - 1, FontObj.Face[i].z - 1, FontObj.UVData[i].x - 1, FontObj.UVData[i].y - 1, FontObj.UVData[i].z - 1, result1, FONT_RESTART);
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
	int uvIndex = 0;
	glm::vec3* vertex = new glm::vec3[vertexnum];
	glm::vec3* face = new glm::vec3[facenum];
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
			fscanf(path, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &temp_face[0], &temp_uv[0], &temp_normal[0], &temp_face[1], &temp_uv[1], &temp_normal[1], &temp_face[2], &temp_uv[2], &temp_normal[2]);
			face[faceIndex].x = temp_face[0]; face[faceIndex].y = temp_face[1]; face[faceIndex].z = temp_face[2];
			uvdata[faceIndex].x = temp_uv[0]; uvdata[faceIndex].y = temp_uv[1]; uvdata[faceIndex].z = temp_uv[2];
			faceIndex++;
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
	
	FontObj.VertexIndex = vertIndex;
	FontObj.FaceIndex = faceIndex;
	FontObj.UVIndex = uvIndex;

	fclose(path);
}

void FONT::RotateRadian() 
{
	Radian += 90;

}

void FONT::Draw(int V1, int V2, int V3, int U1, int U2, int U3) {
	GLfloat POS[3][3] = {
		{FontObj.Vertex[V1].x,FontObj.Vertex[V1].y, FontObj.Vertex[V1].z},
		{FontObj.Vertex[V2].x,FontObj.Vertex[V2].y, FontObj.Vertex[V2].z},
		{FontObj.Vertex[V3].x,FontObj.Vertex[V3].y, FontObj.Vertex[V3].z}
	};
	GLfloat TEX[3][2] = {
		{FontObj.UV[U1].x, FontObj.UV[U1].y},
		{FontObj.UV[U2].x, FontObj.UV[U2].y},
		{FontObj.UV[U3].x, FontObj.UV[U3].y}
	};

	{

		unsigned int location = GET_SHADER->GetLocation("Model", PROGRAM_FONT);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(result));

	}

	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(POS), POS, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TEX), TEX, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

	{
		if (Status == FONT_START)
		{
			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, Texture);
		}
		else if (Status == FONT_PAUSE)
		{
			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, TextureUiPause);
		}
		else if (Status == FONT_RESTART)
		{
			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, TextureUiRestart);
			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, TextureUiResume);
		}
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void FONT::DrawFont(int V1, int V2, int V3, int U1, int U2, int U3, glm::mat4 Res, int eNum) {
	GLfloat POS[3][3] = {
		{FontObj.Vertex[V1].x,FontObj.Vertex[V1].y, FontObj.Vertex[V1].z},
		{FontObj.Vertex[V2].x,FontObj.Vertex[V2].y, FontObj.Vertex[V2].z},
		{FontObj.Vertex[V3].x,FontObj.Vertex[V3].y, FontObj.Vertex[V3].z}
	};
	GLfloat TEX[3][2] = {
		{FontObj.UV[U1].x, FontObj.UV[U1].y},
		{FontObj.UV[U2].x, FontObj.UV[U2].y},
		{FontObj.UV[U3].x, FontObj.UV[U3].y}
	};

	{
		unsigned int location = GET_SHADER->GetLocation("Model", PROGRAM_FONT);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(Res));

	}

	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(POS), POS, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TEX), TEX, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

	{
		if (eNum == FONT_START)
		{
			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, Texture);
		}
		else if (eNum == FONT_PAUSE)
		{
			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, TextureUiPause);
		}
		else if (eNum== FONT_RESTART)
		{
			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, TextureUiRestart);
		}
		else if (eNum== FONT_RESUME)
		{
			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, TextureUiResume);
		}
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
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

void  FONT::FontOut() {
	TransFont.x += 100;
	TransFont.y += 100;
	TransFont.z += 100;
}
void  FONT::FontIn() {
	TransFont.x = 0.8;
	TransFont.y = 0.8;
	TransFont.z = 0;
}
void  FONT::FontPause() {
	TransFont.x = 0;
	TransFont.y = 0;
	TransFont.z = 0;
}