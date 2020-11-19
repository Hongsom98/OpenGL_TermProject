#pragma once
#include <iostream>
#include <string>
#include <io.h>
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"
#pragma comment (lib, "fmodex_vc.lib")
#pragma comment (lib, "fmodex64_vc.lib")

class CFmodSound
{
private:
	FMOD_SYSTEM* m_pSystem;
	FMOD_SOUND** m_ppBGSound;
	FMOD_SOUND** m_ppEFFSound;
	FMOD_CHANNEL** m_ppBGChannel;
	int m_nEFSoundCount;
	int m_nBGSoundCount;
public:
	void CreateEffectSound(int nCount, std::string* SoundFileName);
	void CreateBGSound(int nCount, std::string* SoundFileName);
	void PlaySoundEffect(int nIndex);
	void PlaySoundBG(int nIndex);
	void StopSoundBG(int nIndex);
	void ReleaseSound();
	void Update();

public:
	CFmodSound(void);
	~CFmodSound(void);
};
