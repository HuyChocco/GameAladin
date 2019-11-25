#include "AnimBall.h"

AnimBall::AnimBall()
{


	RECT* listSprite = LoadRect((char*)"Resources\\GameItem\\animball.txt");
	Animation * anim = new Animation(100);
	for (int i = 0; i < 15; i++)
	{
		Sprite * sprite = new Sprite(ANIMBALL_TEXTURE_LOCATION, listSprite[i], ANIMBALL_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	anim->setIsAnimObject(true);
	animations.push_back(anim);
}
AnimBall::~AnimBall()
{

}



void AnimBall::Update(DWORD dt)
{

}
void AnimBall::Render()
{

	for (int i = 0; i < spritedatalist.size(); i++)
	{
		this->GetAnimationsList()[0]->Render(spritedatalist[i]);
	}

}
RECT * AnimBall::LoadRect(char * path)
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

		spriteData.width = ANIMBALL_SPRITE_WIDTH;
		spriteData.height = ANIMBALL_SPRITE_HEIGHT;
		spriteData.x = l;
		spriteData.y = Game::GetInstance()->GetTiledMap()->GetHeight() - t;
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = false;
		spriteData.isFlipped = false;

		spritedatalist.push_back(spriteData);


	}

	f.close();
	return arrayRect;
}