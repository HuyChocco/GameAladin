﻿#include "Enemy2.h"

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
void Enemy2::LoadContent()
{
	RECT* listSprite = this->LoadRect((char*)"Resources\\Enemy\\Enemy2.txt");
	// ENEMY2_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY2_ANI_WALK
	anim = new Animation(100);
	for (int i = 0; i < 8; i++)
	{
		Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY2_ANI_ACTION_WHEN_STANDING
	anim = new Animation(100);
	for (int i = 8; i < 14; i++)
	{
		Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY2_ANI_ATTACK_1
	anim = new Animation(100);
	for (int i = 14; i < 20; i++)
	{
		Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY2_ANI_ATTACK_2
	anim = new Animation(100);
	for (int i = 20; i < 25; i++)
	{
		Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY2_ANI_GET_HIT_1
	anim = new Animation(100);
	for (int i = 25; i < 31; i++)
	{
		Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY2_ANI_GET_HIT_2
	anim = new Animation(100);
	for (int i = 31; i < 40; i++)
	{
		Sprite * sprite = new Sprite(ENEMY2_TEXTURE_LOCATION, listSprite[i], ENEMY2_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	
}
Enemy2::~Enemy2()
{

}



void Enemy2::Update(DWORD dt)
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
				if (this->GetEnumState() == eEnemyState::EnemyATTACK1&&this->GetAnimationList()[3]->IsDone() == true)
				{
					Aladin* player = Aladin::GetInstance();
					player->SetIsHurting(true);
					this->GetAnimationList()[3]->SetIsDone(false);
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
void Enemy2::MoveToObject(GameObject* otherObject)
{
	float otherPositionX = otherObject->GetPositionX();
	float otherPositionY = otherObject->GetPositionY();

	float enemyPositionX = this->GetPositionX();
	float enemyPositionY = this->GetPositionY();

	int currentState = this->GetEnumState();
	
	if (currentState != eEnemyState::EnemyHURT1 &&currentState != eEnemyState::EnemyHURT2 && currentState != eEnemyState::EnemyDIE && currentState != eEnemyState::EnemyATTACK1&&currentState != eEnemyState::EnemyATTACK2)
	{
		if (otherPositionX > enemyPositionX&&abs(otherPositionX - enemyPositionX) < SCREEN_WIDTH)
		{
			
			if (abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH / 3)
			{
				this->isLeft = false;
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyATTACK1);//attack
			}
			else if (abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH / 2)
			{
				this->isLeft = false;
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyACTIONWHENSTAND);//attack
			}
			else
			{
				this->isLeft = false;
				this->SetSpeedX(ENEMY_WALK_SPEED);//move right

				this->SetEnumState(eEnemyState::EnemyWALK);
			}
		}
		else if (otherPositionX < enemyPositionX&&abs(enemyPositionX - otherPositionX )< SCREEN_WIDTH)
		{
			
			if (abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH/3)
			{
				this->isLeft = true;
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyATTACK1);//attack
			}
			else if (abs(enemyPositionX - otherPositionX) < SCREEN_WIDTH / 2)
			{
				this->isLeft = true;
				this->SetSpeedX(0);//stop
				this->SetSpeedY(0);
				this->SetEnumState(eEnemyState::EnemyACTIONWHENSTAND);//attack
			}
			else
			{
				this->isLeft = true;
				this->SetSpeedX(ENEMY_WALK_SPEED*-1);//move left

				this->SetEnumState(eEnemyState::EnemyWALK);
			}
		}
		
	}
	else
	{
		if (this->IsCollide(Aladin::GetInstance()))//nếu xảy ra va chạm
		{

			if (Aladin::GetInstance()->GetStateNumber() == ALADIN_ANI_ATTACK || Aladin::GetInstance()->GetStateNumber() == ALADIN_ANI_ATTACK_WHEN_SIT_DOWN)
				Bleeding();
		}
		if (this->GetAnimationList()[5]->IsDone() == true)
		{
			this->SetEnumState(eEnemyState::EnemyATTACK1);//attack
			this->GetAnimationList()[5]->SetIsDone(false);
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
void Enemy2::Bleeding()
{

	this->SetSpeedX(0);
	this->SetSpeedY(0);
	if(this->GetEnumState()== eEnemyState::EnemyATTACK1)
		Sound::getInstance()->Play(S_SWORD_CHING);
	if (Aladin::GetInstance()->GetAnimationsList()[ALADIN_ANI_ATTACK]->IsDone() == true)
	{
		this->SetEnumState(eEnemyState::EnemyHURT1);
		bloodCount--;
		Aladin::GetInstance()->GetAnimationsList()[ALADIN_ANI_ATTACK]->SetIsDone(false);
		Sound::getInstance()->Play(S_AAAH);
	}
	else if (Aladin::GetInstance()->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->IsDone() == true)
	{
		this->SetEnumState(eEnemyState::EnemyHURT1);
		bloodCount--;
		Aladin::GetInstance()->GetAnimationsList()[ALADIN_ANI_ATTACK_WHEN_SIT_DOWN]->SetIsDone(false);
		Sound::getInstance()->Play(S_AAAH);
	}
}
void Enemy2::Render()
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
		case eEnemyState::EnemyWALK:
			this->GetAnimationList()[1]->Render(spriteData);
			break;
		case eEnemyState::EnemyACTIONWHENSTAND:
			this->GetAnimationList()[2]->Render(spriteData);
			break;
		case eEnemyState::EnemyATTACK1:
			this->GetAnimationList()[4]->Render(spriteData);
			break;
		case eEnemyState::EnemyATTACK2:
			this->GetAnimationList()[4]->Render(spriteData);
			break;
		case eEnemyState::EnemyHURT1:
			this->GetAnimationList()[5]->Render(spriteData);
			break;
		case eEnemyState::EnemyHURT2:
			this->GetAnimationList()[6]->Render(spriteData);
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
			Sound::getInstance()->PlayNew(S_CLOUD_POOF);

		}
		default:
			break;
		}
	}

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