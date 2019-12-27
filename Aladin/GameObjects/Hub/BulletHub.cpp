
#include "BulletHub.h"
BulletHUD *BulletHUD::__instance = NULL;
BulletHUD::BulletHUD()
{
	LoadResource();
	SetText(Aladin::GetInstance()->bulletAppleNum);
	
}
void BulletHUD::SetText(int num)
{
	resultString.clear();
	this->numBullet = num;
	stringstream ss;
	ss << this->numBullet;
	string str = ss.str();
	this->numBulletString = str;
	while (!str.empty())
	{
		resultString.push_back(str.substr(0, 1));

		str.erase(0, 1); // Update string 
	}
	
	
}
BulletHUD *BulletHUD::GetInstance()
{
	if (__instance == NULL)
		__instance = new BulletHUD();
	return __instance;
}
void BulletHUD::LoadResource()
{
	RECT* listSprite = LoadRect((char*)"Resources\\GameItem\\bullethud.txt");
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

void BulletHUD::Update(DWORD dt)
{
	

}

void BulletHUD::Render()
{
	Graphics * graphics = Graphics::GetInstance();
	//sprites[this->numBullet]->SetSize(8, 40);
	graphics->DrawWithoutTransformation(sprites[0], SCREEN_WIDTH-60, SCREEN_HEIGHT - 30);//icon
	int i = 0;
	for (auto o : resultString)
	{
		
		int n = std::stoi(o);
		graphics->DrawWithoutTransformation(sprites[n + 1], SCREEN_WIDTH - 40+i*10, SCREEN_HEIGHT - 30);
		i++;
	}
	


}

BulletHUD::~BulletHUD()
{
}
