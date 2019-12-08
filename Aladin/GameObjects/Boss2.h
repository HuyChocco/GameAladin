#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Boss2 :
	public GameObject
{
private:
	static int Boss2Id;
protected:
	int Id;
	//vector<Animation *> animations;
	bool Active;

	static vector<Animation *> animations;
	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Boss2();
	Boss2(int x, int y, int width, int height, string type);
	void LoadContent();
	~Boss2();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetBoss2Id() { return Boss2Id++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
};