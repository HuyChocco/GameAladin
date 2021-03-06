#include "Bat.h"

Bat::Bat()
{



}
Bat::Bat(int x, int y, int width, int height, string type)
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
	SetEnumState(eEnemyState::EnemyIDLE);
	bloodCount = bloodNum = 4;
	this->LoadContent();

}
void Bat::LoadContent()
{

	RECT* listSprite = this->LoadRect((char*)"Resources\\Enemy\\bat.txt");
	// BAT_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(BAT_TEXTURE_LOCATION, listSprite[i], BAT_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// BAT_ANI_PREPARE
	anim = new Animation(100);
	for (int i = 0; i < 4; i++)
	{
		Sprite * sprite = new Sprite(BAT_TEXTURE_LOCATION, listSprite[i], BAT_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// BAT_ANI_FLY
	anim = new Animation(100);
	for (int i = 4; i <11; i++)
	{
		Sprite * sprite = new Sprite(BAT_TEXTURE_LOCATION, listSprite[i], BAT_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	
}
Bat::~Bat()
{

}



void Bat::Update(DWORD dt)
{
	if (bloodCount == 0)
	{
		SetEnumState(eEnemyState::EnemyDIE);
		if (enemyExplosion == NULL)
		{
			enemyExplosion = new EnemyExplosion();
			enemyExplosion->SetPositionX(this->GetPositionX());
			enemyExplosion->SetPositionY(this->GetPositionY() + this->GetHeight() / 2);
			enemyExplosion->SetWidth(this->GetWidth());
			enemyExplosion->SetHeight(this->GetHeight());
		}
		else
			enemyExplosion->Update(dt);


		return;
	}
	if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
	{

		this->isActive = true;
		std::vector<LPCOLLISIONEVENT> coEvents;
		std::vector<LPCOLLISIONEVENT> coEventsResult;

		std::vector<GameObject *> mapObjects = Grid::GetInstance()->GetCurObjects();

		this->SetSpeedY(this->GetSpeedY() - ALADIN_GRAVITY);

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
				if (ny == 1)//enemy dang dung tren map
				{
					this->SetSpeedY(0);

					MoveToObject(Aladin::GetInstance());


				}
			}
			if (this->IsCollide(Aladin::GetInstance()))
			{
				if (this->GetEnumState() == eEnemyState::EnemyFLY&&this->GetAnimationList()[2]->GetCurFrame() == 0)
				{
					Aladin* player = Aladin::GetInstance();
					player->SetIsHurting(true);
					this->GetAnimationList()[2]->SetIsDone(false);
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


}
void Bat::MoveToObject(GameObject* otherObject)
{
	float otherPositionX = otherObject->GetPositionX();
	float otherPositionY = otherObject->GetPositionY();

	float enemyPositionX = this->GetPositionX();
	float enemyPositionY = this->GetPositionY();

	int currentState = this->GetEnumState();
	//float deltaScale=this->getScale
	if (currentState != eEnemyState::EnemyHURT1 && currentState != eEnemyState::EnemyDIE && currentState != eEnemyState::EnemyATTACK1)
	{
		if (otherPositionX > enemyPositionX&&abs(otherPositionX - enemyPositionX) < SCREEN_WIDTH)
		{

			if (abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH / 4)
			{
				this->isLeft = false;
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyFLY);//fly
			}
			else if (abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH / 3)
			{
				this->isLeft = false;
				
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyPREPARE);//prepare
			}
		}
		else if (otherPositionX < enemyPositionX&&abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH)
		{

			if (abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH / 4)
			{
				this->isLeft = true;
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyFLY);//fly
			}
			else if (abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH / 3)
			{
				this->isLeft = true;
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyPREPARE);//prepare
			}
		}

	}
	else
	{

		if (this->IsCollide(Aladin::GetInstance()))
		{

			if (Aladin::GetInstance()->GetStateNumber() == ALADIN_ANI_ATTACK || Aladin::GetInstance()->GetStateNumber() == ALADIN_ANI_ATTACK_WHEN_SIT_DOWN)
				Bleeding();
		}
		
		if (otherPositionX >= enemyPositionX)
		{
			isLeft = false;
			if (abs(enemyPositionX - otherPositionX) >= SCREEN_WIDTH / 3)
			{
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyIDLE);
			}
		}
		else if (otherPositionX < enemyPositionX)
		{
			isLeft = true;
			if (abs(enemyPositionX - otherPositionX) >= SCREEN_WIDTH / 3)
			{
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyIDLE);
			}
		}

	}

}
void Bat::Bleeding()
{

	this->SetSpeedX(0);
	this->SetSpeedY(0);
	if (Aladin::GetInstance()->GetAnimationsList()[ALADIN_ANI_ATTACK]->IsDone() == true)
	{
		this->SetEnumState(eEnemyState::EnemyHURT1);
		bloodCount--;
		Aladin::GetInstance()->GetAnimationsList()[ALADIN_ANI_ATTACK]->SetIsDone(false);
	}
	else if (Aladin::GetInstance()->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->IsDone() == true)
	{
		this->SetEnumState(eEnemyState::EnemyHURT1);
		bloodCount--;
		Aladin::GetInstance()->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->SetIsDone(false);
	}
}
void Bat::Render()
{
	if (isActive == true)
	{
		SpriteData spriteData;

		spriteData.width = this->width;
		spriteData.height = this->height;
		spriteData.x = this->x;
		spriteData.y = this->y - this->height - 4;
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = !isLeft;
		spriteData.isFlipped = !isLeft;



		switch (this->GetEnumState())
		{
		case eEnemyState::EnemyIDLE:
			this->GetAnimationList()[0]->Render(spriteData);
			break;
		case eEnemyState::EnemyPREPARE:
			this->GetAnimationList()[1]->Render(spriteData);
			break;
		case eEnemyState::EnemyFLY:
			this->GetAnimationList()[2]->Render(spriteData);
			break;
		
		case eEnemyState::EnemyDIE:
		{
			if (enemyExplosion != NULL)
				enemyExplosion->Render();
			if (enemyExplosion->GetAnimationList()[0]->IsDone() == true)
			{
				this->isActive = false;
				delete enemyExplosion;
				enemyExplosion = NULL;
			}
		}
		break;
		default:
			break;
		}
	}

}

RECT* Bat::LoadRect(char * path)
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
		rect.top = r->bottom;
		rect.bottom = r->top;

		arrayRect[i] = rect;
	}
	f.close();
	return arrayRect;
}