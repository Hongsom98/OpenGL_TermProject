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
		std::cout << MouseXPos << " " << MouseYPos << std::endl;
		
		if (((MouseXPos >= 0.7 && MouseYPos >= 0.7) && (MouseXPos <= 0.9 && MouseYPos <= 0.9)) && (GET_FONT->Status == FONT_PAUSE))
		{
			GET_FONT->Status = FONT_RESTART;
			GET_FONT->FontPause();
			//GET_FONT->RenderUIPause();
		}
		if (((MouseXPos >= -0.7 && MouseYPos >= 0.3) && (MouseXPos <= -0.3 && MouseYPos <= 0.7)) && (GET_FONT->Status == FONT_RESTART))
		{
			GET_FONT->FontIn();
			GET_FONT->Status = FONT_PAUSE;
		}
		if (((MouseXPos >= 0.3 && MouseYPos >= 0.3) && (MouseXPos <= 0.7 && MouseYPos <= 0.7)) && (GET_FONT->Status == FONT_RESTART))
		{
			GET_FONT->FontIn();
			GET_FONT->Status = FONT_PAUSE;
			GET_TILE->TileInit();
			SwitchStage();
		}
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
	if (!GET_PC->NoParticle()) GET_PC->Update();


	GET_BG->Update();
}

void SCENEGAME::Render()
{
	GET_PLAYER->Render();
	GET_TILE->Render();
	
	if(GET_FONT->Status == FONT_PAUSE)
		GET_FONT->RenderUI();
	if(GET_FONT->Status == FONT_RESTART)
		GET_FONT->RenderUIPause();

	if(!GET_PC->NoParticle()) GET_PC->Render();

	//투명한 객체는 제일 마지막에 랜더링
	GET_BG->Render();
}

void SCENEGAME::SwitchStage() {
	GET_PC->ClearList();

	switch (StageNum) {

	case 0:
		GET_TILE->ClearList();
		GET_PLAYER->Load();
		GET_BG->ChangeCol();
		TileGen("stage_test.txt");
		GET_SOUND->RestartSound(false);
		break;
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