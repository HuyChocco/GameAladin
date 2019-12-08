#include "Enemy2.h"
vector<Animation *> Enemy2::animations = vector<Animation *>();
Enemy2::Enemy2()
{

	

}
Enemy2::Enemy2(int x, int y, int width, int height, string type)
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
void Enemy2::LoadContent()
{
	
	RECT* listSprite = this->LoadRect((char*)"Resources\\Enemy\\Enemy2.txt");
	// ENEMY2_ANI_WALK
	Animation * anim = new Animation(100);
	for (int i = 0; i < 9; i++)
	{
		Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY2_ANI_ACTION_WHEN_STANDING
	//anim = new Animation(100);
	//for (int i = 9; i < 15; i++)
	//{
	//	Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
	//// ENEMY2_ANI_ATTACK_1
	//anim = new Animation(100);
	//for (int i = 15; i < 21; i++)
	//{
	//	Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
	// ENEMY2_ANI_ATTACK_2
	//anim = new Animation(100);
	//for (int i = 21; i < 26; i++)
	//{
	//	Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
	//// ENEMY2_ANI_GET_HIT_1
	//anim = new Animation(100);
	//for (int i = 26; i < 32; i++)
	//{
	//	Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
	//// ENEMY2_ANI_GET_HIT_2
	//anim = new Animation(100);
	//for (int i = 32; i < 41; i++)
	//{
	//	Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
}
Enemy2::~Enemy2()
{
	
}



void Enemy2::Update(DWORD dt)
{
	//this->SetSpeedX(-0.25);
	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);//cộng một lượng vx*dt vào position x
	this->SetPositionY(this->GetPositionY() + moveY);//cộng một lượng vx*dt vào position y 
}
void Enemy2::Render()
{
	SpriteData spriteData;
	
	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY() - this->height - 4;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = this->IsLeft();
	spriteData.isFlipped = this->IsFlipped();
	
	this->GetAnimationsList()[0]->Render(spriteData);
	

}

RECT* Enemy2::LoadRect(char * path)
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