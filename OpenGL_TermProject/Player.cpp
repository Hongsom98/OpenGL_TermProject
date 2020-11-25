#include "Player.h"

void PLAYER::Load() {
	ReadObj();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);
	
	Texture = loadBMP("bitmap_player.bmp");
	
	AxisForMove[0].x =	   0; AxisForMove[0].y = 0; AxisForMove[0].z = -1.1f;
	AxisForMove[1].x =	   0; AxisForMove[1].y = 0; AxisForMove[1].z =  1.1f;
	AxisForMove[2].x = -1.1f; AxisForMove[2].y = 0; AxisForMove[2].z =	   0;
	AxisForMove[3].x =  1.1f; AxisForMove[3].y = 0; AxisForMove[3].z =     0;
}

void PLAYER::ReadObj() {
	FILE* path = fopen("cube.obj", "r");
	
	char count[128];
	int vertexnum = 0;
	int facenum = 0;
	int uvnum = 0;
	while (!feof(path)) {
		fscanf(path, "%s", count);
		if (count[0] == 'v' && count[1] == '\0') vertexnum++;
		else if (count[0] == 'f' && count[1] == '\0') facenum++;
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
			face[faceIndex].x = temp_face[0]; face[faceIndex].y = temp_face[1]; face[faceIndex].z = temp_face[2];
			uvdata[faceIndex].x = temp_uv[0]; uvdata[faceIndex].y = temp_uv[1]; uvdata[faceIndex].z = temp_uv[2];
			faceIndex++;
		}
		else if (bind[0] == 'v' && bind[1] == 't' && bind[2] == '\0') {
			fscanf(path, "%f %f\n", &uv[uvIndex].x, &uv[uvIndex].y);
			uvIndex++;
		}
	}

	if (PlayerObj.Vertex != NULL) {
		delete[] PlayerObj.Vertex;
		delete[] PlayerObj.Face;
		PlayerObj.Vertex = NULL;
		PlayerObj.Face = NULL;
		PlayerObj.UV = NULL;
		PlayerObj.UVDate = NULL;
	}

	PlayerObj.Vertex = vertex;
	PlayerObj.Face = face;
	PlayerObj.UV = uv;
	PlayerObj.UVDate = uvdata;

	PlayerObj.VertexIndex = vertIndex;
	PlayerObj.FaceIndex = faceIndex;
	PlayerObj.UVIndex = uvIndex;

	fclose(path);
}

GLuint PLAYER::loadBMP(const char* imagepath) {
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

void PLAYER::Render() {
	GET_CAMERA->SetProjectionTransform(PROGRAM_PLAYER);
	GET_CAMERA->SetViewTransform(PROGRAM_PLAYER);

	
	for (int i = 0; i < PlayerObj.FaceIndex; ++i)
		DrawCube(PlayerObj.Face[i].x - 1, PlayerObj.Face[i].y - 1, PlayerObj.Face[i].z - 1, PlayerObj.UVDate[i].x - 1, PlayerObj.UVDate[i].y - 1, PlayerObj.UVDate[i].z - 1);
}

void PLAYER::DrawCube(int V1, int V2, int V3, int U1, int U2, int U3) {
	GLfloat POS[3][3] = {
		{PlayerObj.Vertex[V1].x, PlayerObj.Vertex[V1].y, PlayerObj.Vertex[V1].z},
		{PlayerObj.Vertex[V2].x, PlayerObj.Vertex[V2].y, PlayerObj.Vertex[V2].z},
		{PlayerObj.Vertex[V3].x, PlayerObj.Vertex[V3].y, PlayerObj.Vertex[V3].z}
	};
	GLfloat TEX[3][2] = {
		{PlayerObj.UV[U1].x, PlayerObj.UV[U1].y},
		{PlayerObj.UV[U2].x, PlayerObj.UV[U2].y},
		{PlayerObj.UV[U3].x, PlayerObj.UV[U3].y}
	};

	GET_SHADER->Activate(PROGRAM_PLAYER);
	{
		unsigned int location = GET_SHADER->GetLocation("Model", PROGRAM_PLAYER);
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
		glActiveTexture(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, Texture);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void PLAYER::PlayerMoveX(float v)
{
	if (v < 0) // keyboard W
	{
		PlayerRotate[0] = v;
		RadStack += v;
		if (RadStack <= -90.f)
		{
			TransInfo.z += 2.f;
			RadStack = 0.f;
		}

		glm::mat4 ZTrans1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f + TransInfo.x, 1.f + TransInfo.y, 1.f + TransInfo.z));

		glm::mat4 Zrotate = glm::rotate(glm::mat4(1.0f), glm::radians(PlayerRotate[0]), glm::vec3(1, 0, 0));

		glm::mat4 ZTrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.f - TransInfo.x, -1.f - TransInfo.y, -1.f - TransInfo.z));

		result = ZTrans * Zrotate * ZTrans1 * result;

	}
	else //keyboard S
	{
		PlayerRotate[0] = v;
		RadStack += v;
		if (RadStack >= 90.f)
		{
			TransInfo.z -= 2.f;
			RadStack = 0.f;
		}

		glm::mat4 ZTrans1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f + TransInfo.x, 1.f + TransInfo.y, -1.f + TransInfo.z));

		glm::mat4 Zrotate = glm::rotate(glm::mat4(1.0f), glm::radians(PlayerRotate[0]), glm::vec3(1, 0, 0));

		glm::mat4 ZTrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.f - TransInfo.x, -1.f - TransInfo.y, 1.f - TransInfo.z));


		result = ZTrans * Zrotate * ZTrans1 * result;
	
	}
	std::cout << result[3][0] << " , " << result[3][1] << " , " << result[3][2] << std::endl;
}

void PLAYER::PlayerMoveZ(float v)
{
	if (v > 0) // keyboard A
	{

		PlayerRotate[1] = v;
		RadStack += v;
		if (RadStack >= 90.f)
		{
			TransInfo.x += 2.f;
			RadStack = 0.f;
		}
		
		glm::mat4 ZTrans1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.f + TransInfo.x, 1.f + TransInfo.y, 0.f + TransInfo.z));

		glm::mat4 Zrotate = glm::rotate(glm::mat4(1.0f), glm::radians(PlayerRotate[1]), glm::vec3(0, 0, 1));

		glm::mat4 ZTrans = glm::translate(glm::mat4(1.0f), glm::vec3(-1.f - TransInfo.x, -1.f - TransInfo.y, 0.f - TransInfo.z));

		//result[3][1] = 1.f;
		result = ZTrans * Zrotate * ZTrans1 * result;
		

	}
	else // keyboard D
	{
		PlayerRotate[1] = v;
		RadStack += v;
		if (RadStack <= -90.f)
		{
			TransInfo.x -= 2.f;
			RadStack = 0.f;
		}


		glm::mat4 ZTrans1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.f + TransInfo.x, 1.f + TransInfo.y , 0.f+ TransInfo.z));

		glm::mat4 Zrotate = glm::rotate(glm::mat4(1.0f), glm::radians(PlayerRotate[1]), glm::vec3(0, 0, 1));

		glm::mat4 ZTrans = glm::translate(glm::mat4(1.0f), glm::vec3(1.f- TransInfo.x , -1.f- TransInfo.y, 0.f- TransInfo.z));

		//result[3][1] = 1.f;
		result = ZTrans * Zrotate * ZTrans1 * result;


	}
	std::cout << result[3][0] << " , " << result[3][1] << " , " << result[3][2] << std::endl;
}

void PLAYER::HandleEvents(unsigned char key, bool press) {
	if(press) 
		switch (key) {
			case 'w':
				if (PlayerState == STAY) {
					PlayerState = MOVEFORWARD;
					TargetRotate[0] = -90.f;
				}
				break;
			case 's':
				if (PlayerState == STAY) {
					PlayerState = MOVEBACK;
					TargetRotate[0] = 90.f;
				}
				break;
			case 'a':
				if (PlayerState == STAY) {
					PlayerState = MOVELEFT;
					TargetRotate[1] = 90.f;
				}
				break;
			case 'd':
				if (PlayerState == STAY) {
					PlayerState = MOVERIGHT;
					//TargetRotate[1] = PlayerRotate[1] - 90;
					TargetRotate[1] = -90.f;
				}
				break;
		}
}

void PLAYER::Update() {
	switch (PlayerState) {
		case STAY:
			break;
		case MOVEFORWARD:
			//PlayerRotate[0] -= ROTATEPERFRAME;
			if (TargetRotate[0] <= 0.f) {
				PlayerMoveX(-1.f);
				++TargetRotate[0];
				if(TargetRotate[0] >= 0.f) PlayerState = STAY;
			}
			break;
		case MOVEBACK:
			//PlayerRotate[0] += ROTATEPERFRAME;
			if (0.f <= TargetRotate[0]) {
				PlayerMoveX(1.f);
				--TargetRotate[0];
				if(TargetRotate[0] <= 0.f) PlayerState = STAY;
			}
			break;
		case MOVELEFT:
			//PlayerRotate[1] += ROTATEPERFRAME;
			if (0.f <= TargetRotate[1]) {
				PlayerMoveZ(1.f);
				--TargetRotate[1];
				if (TargetRotate[1] <= 0.f) PlayerState = STAY;
			}
			break;
		case MOVERIGHT:
			//PlayerRotate[1] -= ROTATEPERFRAME;
			if (0.f >= TargetRotate[1]) {
				PlayerMoveZ(-1.f);
				++TargetRotate[1];
				if (TargetRotate[1] >= 0.f) PlayerState = STAY;
			}
			break;
	}
}