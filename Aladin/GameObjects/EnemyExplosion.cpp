#include "EnemyExplosion.h"
EnemyExplosion *EnemyExplosion::__instance = NULL;
EnemyExplosion::EnemyExplosion()
{
	vx = vy = 0;
	this->isActive = true;
	this->LoadResource();
}
EnemyExplosion *EnemyExplosion::GetInstance()
{
	if (__instance == NULL)
		__instance = new EnemyExplosion();
	return __instance;
}
EnemyExplosion::~EnemyExplosion()
{

}

void EnemyExplosion::init()
{
}
void EnemyExplosion::LoadResource()
{
	RECT* listSprite = LoadRect((char*)"Resources\\Enemy\\enemyexplosion.txt");
	Animation * anim = new Animation(100);
	for (int i = 0; i < 5; i++)
	{
		Sprite * sprite = new Sprite(ENEMY_EXPLOSION_TEXTURE_LOCATION, listSprite[i], ENEMY_EXPLOSION_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	

}

void EnemyExplosion::Update(DWORD dt)
{
	if (this->GetAnimationList()[0]->IsDone() == true)
	{
		this->isActive == false;
		this->GetAnimationList()[0]->SetIsDone(false);
	}
}

void EnemyExplosion::Render()
{
	if (isActive == true)
	{
		SpriteData spriteData;

		spriteData.width = this->width;
		spriteData.height = this->height;
		spriteData.x = this->x;
		spriteData.y = this->y- this->height - 4;
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = false;
		spriteData.isFlipped = false;
		this->GetAnimationList()[0]->Render(spriteData);
	}
}

RECT * EnemyExplosion::LoadRect(char * path)
{
	vector<RECT*> listRect;

	fstream f;

	f.open(path, ios::in);

	int number_of_rect;
	string data;

	getline(f, data);
	stringstream stream_data;
	stream_data << data;
	stream_data >> number_of_rect;
	RECT* arrayRect = new RECT[number_of_rect];
	//top-bottom-left-right
	//int top, bottom, left, right;
	for (int i = 0; i < number_of_rect; i++)
	{
		data = "";
		stream_data.clear();

		getline(f, data);
		stream_data << data;

		RECT* r = new RECT();
		stream_data >> r->left;
		stream_data >> r->top;
		stream_data >> r->right;
		stream_data >> r->bottom;


		RECT rect;
		rect.left = r->left;
		rect.right = r->right;
		rect.top = r->bottom;
		rect.bottom = r->top;

		arrayRect[i] = rect;
	}
	f.close();
	return arrayRect;
}