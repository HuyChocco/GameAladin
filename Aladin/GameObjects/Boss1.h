#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Boss1 :
	public GameObject
{
private:
	static int Boss1Id;
protected:
	int Id;
	//vector<Animation *> animations;
	bool Active;

	static vector<Animation *> animations;
	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Boss1();
	Boss1(int x, int y, int width, int height, string type);
	void LoadContent();
	~Boss1();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetBoss1Id() { return Boss1Id++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
};