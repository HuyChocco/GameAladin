#pragma once
#include"Scene.h"
#include "../GameComponents/Viewport.h"
#include "../GameComponents/Sprite.h"
#include "../GameObjects/Aladin.h"
#include "../lib/Tmx.h.in"

class Aladin;



class SceneLV1 : public Scene
{
private:
	std::vector<Sprite*> _backgroundTextures;
	Aladin *aladin;
	vector<GameObject*>_listStaticObject;
	vector<GameObject*> _listObject;
public:
	SceneLV1();
	~SceneLV1();
	void LoadContent(char* filePath);
	void Update(float dt);
	void Draw();
};
