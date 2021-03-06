#include "AnimNail.h"

AnimNail::AnimNail()
{



}
AnimNail::AnimNail(int x, int y, int width, int height, string type)
{
	this->x = x;
	this->y = TiledMap::GetInstance()->GetHeight() - y;
	this->width = width;
	this->height = height;
	this->type = type;
	vx = vy = 0;
	this->isActive = true;
	collider.x = this->x;
	collider.y = this->y;
	collider.vx = this->vx;
	collider.vy = this->vy;
	collider.width = this->width;
	collider.height = this->height;



	SpriteData spriteData;

	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->x;
	spriteData.y = this->y;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = false;
	spriteData.isFlipped = false;
	spritedatalist.push_back(spriteData);
	RECT* listSprite = LoadRect((char*)"Resources\\GameItem\\AnimNail.txt");
	Animation * anim = new Animation(250);
	for (int i = 0; i < 5; i++)
	{
		Sprite * sprite = new Sprite(ANIMNAIL_TEXTURE_LOCATION, listSprite[i], ANIMNAIL_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	anim->setIsAnimObject(true);
	animations.push_back(anim);
}
AnimNail::~AnimNail()
{

}



void AnimNail::Update(DWORD dt)
{
	if (this->GetAnimationsList()[0]->GetCurFrame() == 4)

	{
		this->isDamage = true;
		this->isActive = true;
	}
	else

	{
		this->isDamage = false;
		this->isActive = false;
	}
}
void AnimNail::Render()
{

	for (int i = 0; i < spritedatalist.size(); i++)
	{
		this->GetAnimationsList()[0]->Render(spritedatalist[i]);
	}

}
RECT * AnimNail::LoadRect(char * path)
{
	vector<RECT*> listRect;
	RECT* arrayRect = new RECT[100];
	fstream f;

	f.open(path, ios::in);

	int number_of_rect;
	string data;

	getline(f, data);
	stringstream stream_data;
	stream_data << data;
	stream_data >> number_of_rect;


	for (int i = 0; i < number_of_rect; i++)
	{
		stringstream stream_data;
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
		rect.top = r->top;
		rect.bottom = r->bottom;


		arrayRect[i] = rect;
	}




	f.close();
	return arrayRect;
}