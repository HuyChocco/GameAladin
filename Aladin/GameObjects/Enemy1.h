#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
#include "Enemy.h"
class GameObject;
class Enemy1 :
	public Enemy
{
private:
	static int Enemy1Id;
	//float timeToFire = 50;

	float countTimeToFire = 0;

protected:
	int Id;
	
	bool Active;

	static vector<Animation *> animations;
	vector<SpriteData> spritedatalist;
	
public:
	Enemy1();
	Enemy1(int x, int y, int width, int height, string type);
	void LoadContent();
	~Enemy1();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetEnemy1Id() { return Enemy1Id++; }
	int GetId() { return this->Id; }

	virtual void Update(DWORD dt);
	virtual void Render();

	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
};