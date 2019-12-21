#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Bowl :
	public GameObject
{
private:
	static int BowlId;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;

	int state;
	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Bowl();
	Bowl(int x, int y, int width, int height, string type);
	~Bowl();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetBowlId() { return BowlId++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();

};