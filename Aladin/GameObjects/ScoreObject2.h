#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class ScoreObject2 :
	public GameObject
{
private:
	static int ScoreObject2Id;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;


	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	ScoreObject2();
	ScoreObject2(int x, int y, int width, int height, string type);
	~ScoreObject2();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetScoreObject2Id() { return ScoreObject2Id++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();

};