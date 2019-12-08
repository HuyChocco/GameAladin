#include "Enemy3.h"
vector<Animation *> Enemy3::animations = vector<Animation *>();
Enemy3::Enemy3()
{



}
Enemy3::Enemy3(int x, int y, int width, int height, string type)
{

	this->x = x;
	this->y = TiledMap::GetInstance()->GetHeight() - y;
	this->width = width;
	this->height = height;
	this->type = type;
	vx = vy = 0;

	collider.x = this->x;
	collider.y = this->y;
	collider.vx = this->vx;
	collider.vy = this->vy;
	collider.width = this->width;
	collider.height = this->height;

	this->LoadContent();

}
void Enemy3::LoadContent()
{

	RECT* listSprite = this->LoadRect((char*)"Resources\\Enemy\\Enemy3.txt");
	// Enemy3_ANI_WALK
	Animation * anim = new Animation(100);
	for (int i = 0; i < 9; i++)
	{
		Sprite * sprite = new Sprite(ENEMY3_TEXTURE_LOCATION, listSprite[i], ENEMY3_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//// Enemy3_ANI_ATTACK
	//anim = new Animation(100);
	//for (int i = 9; i < 15; i++)
	//{
	//	Sprite * sprite = new Sprite(Enemy3_TEXTURE_LOCATION, listSprite[i], Enemy3_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
	//// Enemy3_ANI_GET_HIT
	//anim = new Animation(100);
	//for (int i = 15; i < 24; i++)
	//{
	//	Sprite * sprite = new Sprite(Enemy3_TEXTURE_LOCATION, listSprite[i], Enemy3_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
}
Enemy3::~Enemy3()
{

}



void Enemy3::Update(DWORD dt)
{

}
void Enemy3::Render()
{
	SpriteData spriteData;

	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->x;
	spriteData.y = this->y - this->height - 4;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = false;
	spriteData.isFlipped = false;
	this->GetAnimationsList()[0]->Render(spriteData);


}

RECT* Enemy3::LoadRect(char * path)
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



		//r->right += r->left;
		//r->bottom += r->top;

		RECT rect;
		rect.left = r->left;
		rect.right = r->right;
		rect.top = r->bottom;
		rect.bottom = r->top;

		//listRect.push_back(r);
		arrayRect[i] = rect;
	}
	f.close();
	return arrayRect;
}