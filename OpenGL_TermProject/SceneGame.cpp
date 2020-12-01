#include "SceneGame.h"

SCENEGAME::SCENEGAME()
{
	std::cout << "Scene Game" << std::endl;

	TileGen("stage_test.txt");
	StageNum = 0;
}

SCENEGAME::~SCENEGAME()
{

}

void SCENEGAME::Init()
{

}

void SCENEGAME::HandleEvents(unsigned char key, bool press)
{
	if (press)
		switch (key) {
		case VK_RETURN:
			break;
		case VK_ESCAPE:
			glutLeaveMainLoop();
			break;
		case 'w':
		case 's':
		case 'a':
		case 'd':
			GET_PLAYER->HandleEvents(key, press);
			break;
		}
}

void SCENEGAME::HandleEvents(int key, bool press)
{
	if (press)
		switch (key) {
			case GLUT_KEY_UP:
			case GLUT_KEY_DOWN:
			case GLUT_KEY_LEFT:
			case GLUT_KEY_RIGHT:
				GET_PLAYER->HandleEvents(key, press);
				break;
		}
}

void SCENEGAME::HandleEvents(int button, int state, int x, int y)
{

}

void SCENEGAME::Update()
{
	GET_PLAYER->Update();
	if (GET_TILE->Update()) {
		StageNum++;
		std::cout << StageNum << std::endl;
		SwitchStage();
	}
}

void SCENEGAME::Render()
{
	GET_PLAYER->Render();
	GET_TILE->Render();
}

void SCENEGAME::SwitchStage() {
	switch (StageNum) {
	case 1:
		GET_TILE->ClearList();
		GET_PLAYER->Load();
		TileGen("stage_test2.txt");
		break;
	case 2:
		break;
	default:
		break;
	}
}

void SCENEGAME::TileGen(const char* StagePath) {
	FILE* file = fopen(StagePath, "r");

	while (!feof(file)) {
		int TempType;
		float TempTrans[3];
		glm::vec2 TempLoc;
		fscanf(file, "%d %f %f %f %f %f\n", &TempType, &TempTrans[0], &TempTrans[1], &TempTrans[2], &TempLoc.x, &TempLoc.y);

		GET_TILE->Load(TempType, TempTrans, TempLoc);
	}


	fclose(file);
}