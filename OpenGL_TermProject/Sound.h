#pragma once
#include <iostream>
#include <dshow.h>
#include <Windows.h>
#pragma comment (lib, "strmiids.lib")
#define GET_SOUND SOUND::Instance()

class SOUND
{

private:
	bool Restart{ false };

	IGraphBuilder* pGraph = NULL;
	IMediaControl* pControl = NULL;
	IMediaEvent* pEvent = NULL;

	HRESULT hr = CoInitialize(NULL);

public:
	void PlayerEffect();
	void PlayerVictory();
	void PlayerDeath();
	void RestartSound(bool isTrue);

public:
	static SOUND* Instance() {
		static SOUND* SoundInstance = nullptr;
		if (SoundInstance == nullptr)
			SoundInstance = new SOUND;

		return SoundInstance;
	}
};
