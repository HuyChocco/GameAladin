#include "Apple.h"

Apple::Apple()
{



}
Apple::Apple(int x, int y, int width, int height, string type)
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

	RECT* listSprite = LoadRect((char*)"Resources\\GameItem\\apple.txt");
	
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(L"Resources\\GameItem\\items.png", listSprite[i], APPLE_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}

	animations.push_back(anim);
	listSprite = LoadRect((char*)"Resources\\GameItem\\appleexplosion.txt");
	 anim = new Animation(100);
	for (int i = 0; i < 4; i++)
	{
		Sprite * sprite = new Sprite(L"Resources\\GameItem\\items.png", listSprite[i], APPLE_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}

	animations.push_back(anim);
	state = 0;
	
}
Apple::~Apple()
{

}



void Apple::Update(DWORD dt)
{
	if (this->isActive == false)
		state = 1;
}
void Apple::Render()
{
	
	SpriteData spriteData;

	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->x;
	spriteData.y = this->y;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = false;
	spriteData.isFlipped = false;
	if (state == 1)
	{
		if (this->GetAnimationsList()[1]->IsDone())
			return;
		this->GetAnimationsList()[1]->Render(spriteData);
	}
	else
		this->GetAnimationsList()[0]->Render(spriteData);


}
RECT * Apple::LoadRect(char * path)
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