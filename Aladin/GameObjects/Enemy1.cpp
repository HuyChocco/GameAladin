#include "Enemy1.h"

Enemy1::Enemy1()
{
	


}
Enemy1::Enemy1(int x, int y, int width, int height, string type)
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
	bloodCount = bloodNum = 10;
	this->LoadContent();
	
}
void Enemy1::LoadContent()
{
	
	RECT* listSprite = this->LoadRect((char*)"Resources\\Enemy\\Enemy1.txt");
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(ENEMY1_TEXTURE_LOCATION, listSprite[i], ENEMY1_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY1_ANI_WALK
	anim = new Animation(100);
	for (int i = 0; i < 9; i++)
	{
		Sprite * sprite = new Sprite(ENEMY1_TEXTURE_LOCATION, listSprite[i], ENEMY1_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY1_ANI_ATTACK
	anim = new Animation(100);
	for (int i = 9; i < 15; i++)
	{
		Sprite * sprite = new Sprite(ENEMY1_TEXTURE_LOCATION, listSprite[i], ENEMY1_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// ENEMY1_ANI_GET_HIT
	anim = new Animation(100);
	for (int i = 15; i < 24; i++)
	{
		Sprite * sprite = new Sprite(ENEMY1_TEXTURE_LOCATION, listSprite[i], ENEMY1_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}
Enemy1::~Enemy1()
{

}



void Enemy1::Update(DWORD dt)
{
	if (bloodCount == 0)
	{
		SetEnumState(eEnemyState::EnemyDIE);
		this->isActive = false;
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
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		this->isActive = false;
	}
	

}
void Enemy1::MoveToObject(GameObject* otherObject)
{
	float otherPositionX = otherObject->GetPositionX();
	float otherPositionY = otherObject->GetPositionY();

	float enemyPositionX = this->GetPositionX();
	float enemyPositionY = this->GetPositionY();

	int currentState = this->GetEnumState();
	//float deltaScale=this->getScale
	if (currentState != eEnemyState::EnemyHURT && currentState != eEnemyState::EnemyDIE && currentState!=eEnemyState::EnemyATTACK)
	{
		if (otherPositionX > enemyPositionX&&otherPositionX - enemyPositionX < SCREEN_WIDTH)
		{
			this->isLeft = false;
			this->SetSpeedX(ENEMY_WALK_SPEED);//move right
			
			this->SetEnumState(eEnemyState::EnemyWALK);
		}
		else if (otherPositionX < enemyPositionX&&enemyPositionX - otherPositionX < SCREEN_WIDTH)
		{
			this->isLeft = true;
			this->SetSpeedX(ENEMY_WALK_SPEED*-1);//move left
			
			this->SetEnumState(eEnemyState::EnemyWALK);
		}
		if (abs(enemyPositionX - otherPositionX) < this->GetWidth()*1.5)
		{
			this->SetSpeedX(0);//stop
			this->SetSpeedY(0);
			this->SetEnumState(eEnemyState::EnemyATTACK);//attack
		}
	}
	else
	{
		if (this->IsCollide(Aladin::GetInstance()))
		{
			
			if (Aladin::GetInstance()->GetStateNumber() == ALADIN_ANI_ATTACK|| Aladin::GetInstance()->GetStateNumber()==ALADIN_ANI_ATTACK_WHEN_SIT_DOWN)
				Bleeding();
		}
		else
		{
			this->SetEnumState(eEnemyState::EnemyIDLE);
			this->SetSpeedX(0);
		}
		
	}
	
}
void Enemy1::Bleeding()
{
	
	this->SetSpeedX(0);
	this->SetSpeedY(0);
	if (this->GetAnimationList()[3]->GetCurFrame() == 0)
	{
		this->SetEnumState(eEnemyState::EnemyHURT);
		bloodCount--;
		
	}
	

}
void Enemy1::Render()
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
		case eEnemyState::EnemyHURT:
			this->GetAnimationList()[3]->Render(spriteData);
			break;
		case eEnemyState::EnemyATTACK:
			this->GetAnimationList()[2]->Render(spriteData);
			break;
		default:
			break;
		}
	}
	
}

RECT* Enemy1::LoadRect(char * path)
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