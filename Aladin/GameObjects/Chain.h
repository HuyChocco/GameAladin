#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Chain :
	public GameObject
{
private:
	static int ChainId;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;


	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Chain();
	Chain(int x, int y, int width, int height, string type);
	~Chain();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetChainId() { return ChainId++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();

};