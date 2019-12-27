#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Sprite.h"
#include "Graphics.h"


using namespace std;

class Animation
{
	DWORD lastFrameTime;
	DWORD defaultDelayTime;

	vector< pair<Sprite *, DWORD> > frames;
	int curFrame;
	bool done = false;
	bool isStop = false;
	bool isAttack = false;
	bool isSitDown = false;
	bool isAnimObject = false;
	bool isReverse = false;
	bool isActionWhenStand = false;
	int timeToTrans = 0;
	
	//cherry's animations
	//bool isExplosion = false;
public:
	SpriteData spriteData;
	Animation(DWORD defaultDelayTime) { this->defaultDelayTime = defaultDelayTime; };
	~Animation() { frames.clear(); };
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }
	DWORD GetLastFrameTime() { return this->lastFrameTime; }	
	int GetCurFrame() { return curFrame; }
	bool IsDone() { return done; }
	void SetIsDone(bool done) { this->done=done; }
	void setIsStop(bool isStop) { this->isStop = isStop; }
	void setIsReverse(bool isReverse) { this->isReverse = isReverse; }
	bool IsReverse() { return this->isReverse; }
	bool IsStop() { return this->isStop; }
	void setIsSitDown(bool isSitDown) { this->isSitDown = isSitDown; }
	bool IsSitDown() { return this->isSitDown; }
	void setIsAttack(bool isAttack) { this->isAttack = isAttack; }
	bool IsAttack() { return this->isAttack; }
	void setIsAnimObject(bool isAnimObject) { this->isAnimObject = isAnimObject; }
	bool IsActionWhenStand() { return this->isActionWhenStand; }
	void setIsActionWhenStand(bool isActionWhenStand) { this->isActionWhenStand = isActionWhenStand; }
	bool IsAnimObject() { return this->isAnimObject; }
	//void setIsExplosion(bool isExplosion) { this->isExplosion = isExplosion; }
	//bool IsExplosion() { return this->isExplosion; }
	void Reset() { curFrame = -1; }

	void AddFrame(Sprite *sprite, DWORD time = 0);
	void Render(SpriteData spriteData);
};

