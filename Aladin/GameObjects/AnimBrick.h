#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class AnimBrick :
	public GameObject
{
private:
	static int AnimBrickId;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;
	
	
	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	AnimBrick();
	~AnimBrick();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetAnimBrickId() { return AnimBrickId++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();
	
};