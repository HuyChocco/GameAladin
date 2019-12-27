#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
#include "EnemyExplosion.h"
class GameObject;
class Enemy3 :
	public GameObject
{
private:
	static int Enemy3Id;
	vector<Animation *> animations;

	int bloodCount;
	int bloodNum;
	EnemyExplosion * enemyExplosion;
protected:
	eEnemyState eState;



	vector<SpriteData> spritedatalist;

public:
	Enemy3();
	Enemy3(int x, int y, int width, int height, string type);
	void LoadContent();
	~Enemy3();
	RECT* LoadRect(char * path);


	static int GetEnemy3Id() { return Enemy3Id++; }

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