#include "SceneGame.h"

SCENEGAME::SCENEGAME()
{
	std::cout << "Scene Game" << std::endl;

	TileGen("stage_test.txt");
	StageNum = 0;
	BackGroundGen("BackGround_Gen.txt");
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
	
}

void SCENEGAME::HandleEvents(int button, int state, int x, int y)
{
	float MouseXPos, MouseYPos;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		MouseXPos = (float)x / 400 - 1; MouseYPos = ((float)y / 400 - 1) * -1;
		//if(GET_FONT)
	}
}

void SCENEGAME::Update()
{
	GET_PLAYER->Update();
	if (GET_TILE->Update()) {
		StageNum++;
		std::cout << StageNum << std::endl;
		SwitchStage();
	}
	
	GET_BG->Update();
}

void SCENEGAME::Render()
{
	GET_PLAYER->Render();
	GET_TILE->Render();
	GET_FONT->Render();

	//투명한 객체는 제일 마지막에 랜더링
	GET_BG->Render();
}

void SCENEGAME::SwitchStage() {
	switch (StageNum) {
	case 0:
		GET_SOUND->RestartSound(false);
	case 1:
		GET_TILE->ClearList();
		GET_PLAYER->Load();
		GET_BG->ChangeCol();
		TileGen("stage_test2.txt");
		GET_SOUND->RestartSound(false);
		break;
	case 2:
		GET_SOUND->RestartSound(true);
		GET_SOUND->PlayerVictory();
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

void SCENEGAME::BackGroundGen(const char* StagePath) {
	FILE* file = fopen(StagePath, "r");

	while (!feof(file)) {
		float TempTrans[3];

		fscanf(file, "%f %f %f\n", &TempTrans[0], &TempTrans[1], &TempTrans[2]);

		GET_BG->Load(TempTrans);
	}


	fclose(file);
}

const int SCENEGAME::GetStageNum() {
	return StageNum;
}