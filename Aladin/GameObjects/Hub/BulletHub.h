#pragma once
#include "HubObject.h"

class BulletHUD : public HudObject
{
	std::vector<Sprite *> sprites;

	int numBullet;

	Animation * exitAnimation;
	static BulletHUD *__instance;
public:

	BulletHUD();
	static BulletHUD *GetInstance();
	std::vector<Sprite *> GetSpriteList() { return this->sprites; }

	void LoadResource();

	void Update(DWORD dt);

	void Render();

	~BulletHUD();
};