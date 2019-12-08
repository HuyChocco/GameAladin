#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Enemy2 :
	public GameObject
{
private:
	static int Enemy2Id;
protected:
	int Id;
	//vector<Animation *> animations;
	bool Active;

	static vector<Animation *> animations;
	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Enemy2();
	Enemy2(int x, int y, int width, int height, string type);
	void LoadContent();
	~Enemy2();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetEnemy2Id() { return Enemy2Id++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
};