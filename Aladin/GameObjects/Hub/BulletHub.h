#pragma once
#include "HubObject.h"

class BulletHUD : public HudObject
{
	std::vector<Sprite *> sprites;

	int numBullet;
	string numBulletString;
	Animation * exitAnimation;
	static BulletHUD *__instance;
	std::vector<string> resultString;
public:
	void SetText(int num);
	BulletHUD();
	static BulletHUD *GetInstance();
	std::vector<Sprite *> GetSpriteList() { return this->sprites; }

	void LoadResource();

	void Update(DWORD dt);

	void Render();

	~BulletHUD();
};