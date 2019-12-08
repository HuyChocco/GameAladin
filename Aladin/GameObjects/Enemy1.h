#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Enemy1 :
	public GameObject
{
private:
	static int Enemy1Id;
protected:
	int Id;
	//vector<Animation *> animations;
	bool Active;

	static vector<Animation *> animations;
	vector<SpriteData> spritedatalist;
	//Item itemtype;
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