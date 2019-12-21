#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Egg :
	public GameObject
{
private:
	static int EggId;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;
	int state;

	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Egg();
	Egg(int x, int y, int width, int height, string type);
	~Egg();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetEggId() { return EggId++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();

};