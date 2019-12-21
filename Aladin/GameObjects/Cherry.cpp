#include "Cherry.h"

Cherry * Cherry::__instance = NULL;

Cherry * Cherry::GetInstance()
{
	if (__instance == NULL)
		__instance = new Cherry();
	return __instance;
}

Cherry::Cherry()
{
	Aladin * aladin = Aladin::GetInstance();
	this->x = aladin->GetPositionX();
	this->y = aladin->GetPositionY();
	this->width = 16;
	this->height = 16;
	this->type = "bullet";
	vx =  0.125f;
	vy = 0;
	this->isActive = true;
	collider.x = this->x;
	collider.y = this->y;
	collider.vx = this->vx;
	collider.vy = this->vy;
	collider.width = this->width;
	collider.height = this->height;
	

	maxDistance = SCREEN_WIDTH / 2;

	state = CHERRY_HIDDEN;

	this->TimeFly = 25;
	LoadResources();
}

void Cherry::LoadResources()
{
	RECT* listSprite = LoadRect((char*)"Resources\\GameItem\\apple.txt");
	Animation * animation = new Animation(100);
	
	Sprite * sprite = new Sprite(L"Resources\\GameItem\\items.png", listSprite[0], APPLE_TEXTURE_TRANS_COLOR);
	animation->AddFrame(sprite);
	animations.push_back(animation);
	
}

void Cherry::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
	{
		state = CHERRY_ATTACK;
		this->isActive = true;
		std::vector<LPCOLLISIONEVENT> coEvents;
		std::vector<LPCOLLISIONEVENT> coEventsResult;

		std::vector<GameObject *> mapObjects = Grid::GetInstance()->GetCurObjects();

		this->SetSpeedY(this->GetSpeedY() - ALADIN_GRAVITY);
		this->SetSpeedX((Aladin::GetInstance()->IsLeft() ? -1 : 1)*ALADIN_WALK_SPEED);
		coEvents.clear();
		if (dt >= 40)
			dt = 40;
		this->SetDt(dt);

		this->CheckMapCollision(mapObjects, coEvents);

		if (coEvents.size() == 0)
		{
			float moveX = trunc(this->GetSpeedX()* dt);
			float moveY = trunc(this->GetSpeedY()* dt);

			this->SetPositionX(this->GetPositionX() + moveX);
			this->SetPositionY(this->GetPositionY() + moveY);
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * this->GetSpeedX() * dt;
			float moveY = min_ty * this->GetSpeedY() * dt;

			this->SetPositionX(this->GetPositionX() + moveX);
			this->SetPositionY(this->GetPositionY() + moveY);


			if (nx != 0) this->SetSpeedX(0);
			if (ny != 0) this->SetSpeedY(0);

			if (coEventsResult[0]->collisionID == 1)
			{
				this->state = CHERRY_EXPLOSION;
				//if (ny == 1)
				{
					this->SetSpeedY(0);
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		this->isActive = false;
	}
	if (this->isActive)
	{

		

	}
}

void Cherry::CherryAttacking()
{
	

	
}

void Cherry::Render()
{
	Aladin * aladin = Aladin::GetInstance();
	{
		SpriteData spriteEnemyData;

		spriteEnemyData.width = 16;
		spriteEnemyData.height = 16;
		spriteEnemyData.x = this->GetPositionX();
		spriteEnemyData.y = this->GetPositionY();
		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isFlipped =aladin->IsFlipped();
		spriteEnemyData.isLeft = aladin->IsLeft();

		//if (this->state == CHERRY_HIDDEN)
			//this->animations[CHERRY_HIDDEN]->Render(spriteEnemyData);
		if (this->state == CHERRY_ATTACK)
			this->animations[CHERRY_HIDDEN]->Render(spriteEnemyData);
		/*if (this->state == CHERRY_EXPLOSION)
			this->animations[CHERRY_EXPLOSION]->Render(spriteEnemyData);*/
		

		
	}
}

RECT* Cherry::LoadRect(char * path)
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
Cherry::~Cherry()
{
}

