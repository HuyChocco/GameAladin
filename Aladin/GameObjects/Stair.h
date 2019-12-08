#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Stair :
	public GameObject
{
private:
	static int StairId;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;


	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Stair();
	Stair(int x, int y, int width, int height, string type);
	~Stair();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetStairId() { return StairId++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();

};