#pragma once
#include "../GameComponents/GameObject.h"

class EnemyExplosion : public GameObject
{
	static EnemyExplosion *__instance;
	vector<Animation *> animations;
public:
	EnemyExplosion();
	
	~EnemyExplosion();
	static EnemyExplosion *GetInstance();
	virtual void init();
	void LoadResource();
	vector<Animation *> GetAnimationList() { return this->animations; }
	virtual void Update(DWORD dt);
	virtual void Render();
	RECT * LoadRect(char * path);
protected:
};
