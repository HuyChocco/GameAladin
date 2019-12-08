#pragma once
#include"Scene.h"
#include "../GameComponents/Viewport.h"
#include "../GameComponents/Sprite.h"
#include "../GameObjects/Aladin.h"
#include "../lib/Tmx.h.in"

class Aladin;



class SceneLV2 : public Scene
{
private:
	std::vector<Sprite*> _backgroundTextures;
	Aladin *aladin;
	static Scene *__instance;
public:
	SceneLV2();
	~SceneLV2();
	void LoadContent(char* filePath);
	void Update(float dt);
	void Draw();
	static Scene* GetInstance();
};
