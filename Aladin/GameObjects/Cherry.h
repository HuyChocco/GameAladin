#pragma once
#include "../GameComponents/GameObject.h"
#include "State.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "AladinState.h"
class Cherry : public GameObject
{
	int damage = 1;

	vector<Animation *> animations;
	static Cherry * __instance;

	int state;

	

	bool isStart = true;

	bool isReturn = true;

	bool isAladinLeft;

	float maxDistance;

	float distance;

	int TimeFly = 10;
	int countTimeFly = 0;

public:
	Cherry();
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
	int GetDamage() { return this->damage; }

	bool GetIsStart() { return this->isStart; }

	void SetState(int state) { this->state = state; }

	int GetState() { return this->state; }

	void CherryAttacking();

	static Cherry * GetInstance();

	void LoadResources();

	void Update(DWORD dt) override;
	void Render() override;

	float GetDistance() { return this->distance; }
	RECT* LoadRect(char * path);
	~Cherry();
};

