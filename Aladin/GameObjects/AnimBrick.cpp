#include "AnimBrick.h"

AnimBrick::AnimBrick()
{
	
	
	RECT* listSprite = LoadRect((char*)"Resources\\GameItem\\animbrick.txt");
	Animation * anim = new Animation(200);
	for (int i = 0; i < 5; i++)
	{
		Sprite * sprite = new Sprite(ANIMBRICK_TEXTURE_LOCATION, listSprite[i], ANIMBRICK_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	anim->setIsAnimObject(true);
	animations.push_back(anim);
}
AnimBrick::~AnimBrick()
{

}



void AnimBrick::Update(DWORD dt)
{

}
void AnimBrick::Render()
{
	
	for (int i = 0; i < spritedatalist.size(); i++)
	{
		this->GetAnimationsList()[0]->Render(spritedatalist[i]);
	}
	
}
RECT * AnimBrick::LoadRect(char * path)
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
	stream_data.clear();
	getline(f, data);
	int number_of_position;
	stream_data << data;
	stream_data >> number_of_position;
	for (int i = 0; i < number_of_position; i++)
	{
		data = "";
		stream_data.clear();

		getline(f, data);
		stream_data << data;
		int l, t;
		stream_data >> l;
		stream_data >> t;
		SpriteData spriteData;

		spriteData.width = ANIMBRICK_SPRITE_WIDTH;
		spriteData.height = ANIMBRICK_SPRITE_HEIGHT;
		spriteData.x = l;
		spriteData.y = Game::GetInstance()->GetTiledMap()->GetHeight()-t;
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = false;
		spriteData.isFlipped = false;

		spritedatalist.push_back(spriteData);
		
		
	}
	
	f.close();
	return arrayRect;
}