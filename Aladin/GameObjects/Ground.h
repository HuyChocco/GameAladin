#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Game.h"
class GameObject;
class Ground :
	public GameObject
{
private:
	static int GroundId;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;


	vector<SpriteData> spritedatalist;
	//Item itemtype;
public:
	Ground();
	Ground(int x,int y,int width,int height,string type);
	~Ground();
	RECT* LoadRect(char * path);
	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	vector<Animation *> GetAnimationsList() { return animations; }
	static int GetGroundId() { return GroundId++; }
	int GetId() { return this->Id; }
	virtual void Update(DWORD dt);
	virtual void Render();

};