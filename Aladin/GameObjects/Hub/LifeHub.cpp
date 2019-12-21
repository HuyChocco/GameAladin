
#include "LifeHub.h"
LifeHUD *LifeHUD::__instance = NULL;
LifeHUD::LifeHUD()
{
	LoadResource();

	this->numLife = 6;
}
LifeHUD *LifeHUD::GetInstance()
{
	if (__instance == NULL)
		__instance = new LifeHUD();
	return __instance;
}
void LifeHUD::LoadResource()
{
	RECT* listSprite = LoadRect((char*)"Resources\\GameItem\\lifehud.txt");
	Sprite * sprite;

	// icon
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[0], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 0
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[1], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 1
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[2], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 2
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[3], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 3
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[4], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 4
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[5], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 5
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[6], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 6
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[7], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 7
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[8], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 8
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[9], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);

	// 9
	sprite = new Sprite(L"Resources\\GameItem\\item.png", listSprite[10], HUB_TEXTURE_TRANS_COLOR);
	sprites.push_back(sprite);
	
}

void LifeHUD::Update(DWORD dt)
{
	if (numLife >= 0 && numLife <= 6)
		this->numLife = numLife;
}

void LifeHUD::Render()
{
	
	Graphics::GetInstance()->DrawWithoutTransformation(sprites[0], 20, SCREEN_HEIGHT-40);//icon
	Graphics::GetInstance()->DrawWithoutTransformation(sprites[this->numLife+1], 80, SCREEN_HEIGHT - 30);
	
	
}

LifeHUD::~LifeHUD()
{
}
