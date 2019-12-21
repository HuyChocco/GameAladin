#pragma once
#ifndef __SOUND__
#define __SOUND__
#include "Constants.h"
#include "Game.h"
#include "dxaudio.h"

#include <map>
using namespace std;
class Sound
{
public:
	~Sound();
	static Sound* getInstance();
	void loadSound(HWND hWnd);
	void Play(eSoundId soundid);
	void PlayNew(eSoundId soundid);					// nếu sound đang phát thì chạy đè lên
	void Stop(eSoundId soundid);
	void StopAll();
	void PlayLoop(eSoundId soundid);
	bool IsPlaying(eSoundId soundid);
	void setVolume(int vol);
	void setMute(bool mute);
	bool getMute();
private:
	Sound();
	static Sound* _instance;
	map<eSoundId, CSound*> _listSound;
	float _volume;
	bool _mute;
};

#endif 