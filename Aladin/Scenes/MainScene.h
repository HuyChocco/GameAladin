#pragma once

#include "../GameComponents/Viewport.h"
#include "../GameComponents/Sprite.h"

#include "../GameComponents/Scene.h"


class MainScene : public Scene
{
private:
	std::vector<Sprite*> _backgroundTextures;

	//Text *_txtCountApple;
	//Sprite *_spriteCountApple;

	//Text *_txtCountRubby;
	//Sprite *_spriteCountRubby;

	//Text *_txtTimesPlay;
	//Sprite *_spriteTimesPlay;

	//Text *_txtScore;

	//PlayerHealthMeter *_playerHealthMeter;

	int _hurtApple;
	int _hurtHealth;
public:
	MainScene();
	~MainScene();

	void LoadContent();
	void Update(float dt);
	void Draw();
};
