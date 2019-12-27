#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
#include "EnemyExplosion.h"
class GameObject;
class Enemy2 :
	public GameObject
{
private:
	static int Enemy2Id;
	vector<Animation *> animations;

	int bloodCount;
	int bloodNum;
	EnemyExplosion *enemyExplosion;
protected:
	eEnemyState eState;
	vector<SpriteData> spritedatalist;

public:
	Enemy2();
	Enemy2(int x, int y, int width, int height, string type);
	void LoadContent();
	~Enemy2();
	RECT* LoadRect(char * path);


	static int GetEnemy2Id() { return Enemy2Id++; }

	vector<Animation *> GetAnimationList() { return this->animations; }
	virtual void Update(DWORD dt);
	virtual void Render();
	void MoveToObject(GameObject* otherObject);
	void Bleeding();
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
	eEnemyState GetEnumState() { return this->eState; }
	void SetEnumState(eEnemyState estate) { this->eState = estate; }

};