#pragma once
#include"Scene.h"
#include "../GameComponents/Viewport.h"
#include "../GameComponents/Sprite.h"
#include "../GameObjects/Aladin.h"
#include "../lib/Tmx.h.in"
#include"../GameObjects/Hub/LifeHub.h"
#include"../GameObjects/Hub/BulletHub.h"
class Aladin;

class LifeHUD;
class BullletHUD;
class SceneLV1 : public Scene
{
private:
	std::vector<Sprite*> _backgroundTextures;
	Aladin *aladin;
	static Scene *__instance;
	LifeHUD *lifeHUD;
	BulletHUD *bulletHUD;
public:
	SceneLV1();
	~SceneLV1();
	void LoadContent(char* filePath);
	void Update(float dt);
	void Draw();
	static Scene* GetInstance();
};
