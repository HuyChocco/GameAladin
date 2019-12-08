#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class AnimBall :
	public GameObject
{
private:
	static int AnimBallId;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;


	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	AnimBall();
	AnimBall(int x,int y,int width,int height,string type);
	~AnimBall();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetAnimBallId() { return AnimBallId++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();

};