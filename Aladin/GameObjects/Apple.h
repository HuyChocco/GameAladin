#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Apple :
	public GameObject
{
private:
	static int AppleId;
	int state;
protected:
	int Id;
	vector<Animation *> animations;
	

	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Apple();
	Apple(int x, int y, int width, int height, string type);
	~Apple();
	RECT* LoadRect(char * path);
	
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetAppleId() { return AppleId++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();

};