#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Enemy3 :
	public GameObject
{
private:
	static int Enemy3Id;
protected:
	int Id;
	//vector<Animation *> animations;
	bool Active;

	static vector<Animation *> animations;
	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Enemy3();
	Enemy3(int x, int y, int width, int height, string type);
	void LoadContent();
	~Enemy3();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetEnemy3Id() { return Enemy3Id++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
};