#pragma once
#include <iostream>
#include <dshow.h>
#include <Windows.h>
#pragma comment (lib, "strmiids.lib")
#define GET_SOUND SOUND::Instance()

class SOUND
{

private:
	
public:
	void Effect();
	

public:
	static SOUND* Instance() {
		static SOUND* PlayeRInstance = nullptr;
		if (PlayeRInstance == nullptr)
			PlayeRInstance = new SOUND;

		return PlayeRInstance;
	}
};
