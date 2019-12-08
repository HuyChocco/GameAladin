#include "Wall.h"

Wall::Wall()
{



}
Wall::Wall(int x,int y,int width,int height,string type)
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

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = this->width;
	rect.bottom = this->height;
	
	SpriteData spriteData;

	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->x;
	spriteData.y =  this->y;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = false;
	spriteData.isFlipped = false;
	spritedatalist.push_back(spriteData);
	Animation * anim = new Animation(100);

	Sprite * sprite = new Sprite(L"Resources\\GameItem\\apple.png", rect, WALL_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);


	animations.push_back(anim);
}
Wall::~Wall()
{

}



void Wall::Update(DWORD dt)
{

}
void Wall::Render()
{

	//this->GetAnimationsList()[0]->Render(spritedatalist[0]);

}
//RECT * Wall::LoadRect(char * path)
//{
//
//}