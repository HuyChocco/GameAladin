#pragma once
#include "HubObject.h"

class LifeHUD : public HudObject
{
	std::vector<Sprite *> sprites;

	int numLife;

	Animation * exitAnimation;
	static LifeHUD *__instance;
public:

	LifeHUD();
	static LifeHUD *GetInstance();
	std::vector<Sprite *> GetSpriteList() { return this->sprites; }

	void LoadResource();

	void Update(DWORD dt);

	void Render();

	~LifeHUD();
};