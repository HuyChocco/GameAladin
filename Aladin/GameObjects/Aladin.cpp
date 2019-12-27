#include "Aladin.h"

vector<Animation *> Aladin::animations = vector<Animation *>();
Aladin *Aladin::__instance = NULL;

Aladin::Aladin()
{
	

	idleState = new AladinState(this, ALADIN_ANI_IDLE);
	walkState = new AladinState(this, ALADIN_ANI_RUN);
	stopState = new AladinState(this, ALADIN_ANI_STOP);
	jumpState = new AladinState(this, ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS);
	attackState = new AladinState(this, ALADIN_ANI_ATTACK);
	fallingState = new AladinState(this, ALADIN_ANI_FALLING_DOWN);
	actionWhenStandState = new AladinState(this, ALADIN_ANI_ACTION_WHEN_STAND);
	jumpWhenPressingState= new AladinState(this, ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW);
	sitDownState= new AladinState(this, ALADIN_ANI_SIT_DOWN);
	attackWhenSitDownState= new AladinState(this, ALADIN_ANI_ATTACK_WHEN_SIT_DOWN);
	throwCherryInTheAirState= new AladinState(this, ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR);
	throwCherryWhenStandState = new AladinState(this, ALADIN_ANI_THROW_CHERRY_WHEN_STANDING);
	climbTheLadderState = new AladinState(this, ALADIN_ANI_CLIMB_THE_LADDER);
	climbTheRopeState = new AladinState(this, ALADIN_ANI_CLIMB_THE_ROPE);
	playWhenStandState = new AladinState(this, ALADIN_ANI_PLAY_WITH_CHERRY);
	state = idleState;//trạng thái ban đầu cho aladin

	this->x = 60;
	this->y = 300;
	this->width = ALADIN_SPRITE_WIDTH;
	this->height = ALADIN_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = this->width;
	collider.height = this->height;
	this->isActive = true;
	bloodNum = 20;
	LoadResources();
}

Aladin *Aladin::GetInstance()
{
	if (__instance == NULL)
		__instance = new Aladin();
	return __instance;
}
//Nạp các animation cho aladin
void Aladin::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Aladin\\Aladin.txt");
	//// ALADIN_ANI_IDLE
	Animation * animi = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	//// ALADIN_ANI_ACTION_WHEN_STAND
	animi = new Animation(200);
	for (int i = 1; i < 7; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	////ALADIN_ANI_CHERRY_EXPLOSION
	animi = new Animation(100);
	for (int i = 7; i < 13; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	////ALADIN_ANI_PLAY_WITH_CHERRY
	animi = new Animation(100);
	for (int i = 13; i < 45; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	////ALADIN_ANI_THROW_CHERRY_WHEN_STANDING
	animi = new Animation(100);
	for (int i = 45; i < 51; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	////ALADIN_ANI_ATTACK
	animi = new Animation(100);
	for (int i = 51; i < 56; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	////ALADIN_ANI_LOOK_UP
	animi = new Animation(100);
	for (int i = 56; i < 59; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);

	////ALADIN_ANI_SIT_DOWN
	animi = new Animation(100);
	for (int i = 59; i < 63; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	/////ALADIN_ANI_THROW_CHERRY_WHEN_SIT_DOWN
	animi = new Animation(100);
	for (int i = 63; i < 68; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	/////ALADIN_ANI_ATTACK_WHEN_SIT_DOWN
	animi = new Animation(100);
	for (int i = 68; i < 75; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	/////ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW
	animi = new Animation(100);
	for (int i = 75; i < 84; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);

	/////ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS
	animi = new Animation(100);
	for (int i = 84; i < 94; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	/////ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR
	animi = new Animation(100);
	for (int i = 94; i < 99; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);

	/////ALADIN_ANI_ATTACK_WHEN_IN_THE_AIR
	animi = new Animation(100);
	for (int i = 99; i < 105; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	/////ALADIN_ANI_RUN
	animi = new Animation(100);
	for (int i = 105; i < 118; i++)
	{
		Sprite * sprite
			= new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	/////ALADIN_ANI_CLIMB_THE_ROPE
	animi = new Animation(100);
	for (int i = 118; i < 128; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	///////ALADIN_ANI_GET_HIT
	animi = new Animation(100);
	for (int i = 128; i < 134; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	///////ALADIN_ANI_DIE
	animi = new Animation(100);
	for (int i = 134; i < 162; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	///////ALADIN_ANI_STOP
	animi = new Animation(100);
	for (int i = 162; i < 171; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		animi->AddFrame(sprite);
	}
	animations.push_back(animi);
	
}

void Aladin::SetState(State * state)
{
	this->state = state;
}

State * Aladin::GetIdleState()
{
	this->SetStateNumber(ALADIN_ANI_IDLE);
	return idleState;
}

State * Aladin::GetWalkState()
{
	this->SetStateNumber(ALADIN_ANI_RUN);
	return walkState;
}

State * Aladin::GetJumpState()
{
	this->SetStateNumber(ALADIN_ANI_JUMP_WITH_NO_KEY_PRESS);
	return jumpState;
}
State * Aladin::GetAttackState()
{
	this->SetStateNumber(ALADIN_ANI_ATTACK);
	return attackState;
}
State * Aladin::GetFallingState()
{
	this->SetStateNumber(ALADIN_ANI_FALLING_DOWN);
	return fallingState;
}
State * Aladin::GetActionWhenStandState()
{
	this->SetStateNumber(ALADIN_ANI_ACTION_WHEN_STAND);
	return actionWhenStandState;
}
State * Aladin::GetJumpWhenPressingState()
{
	this->SetStateNumber(ALADIN_ANI_JUMP_WHEN_PRESSING_LEFT_OR_RIGHT_ARROW);
	return jumpWhenPressingState;
}
State * Aladin::GetSitDownState()
{
	this->SetStateNumber(ALADIN_ANI_SIT_DOWN);
	return sitDownState;
}
State * Aladin::GetAttackWhenSitDownState()
{
	this->SetStateNumber(ALADIN_ANI_ATTACK_WHEN_SIT_DOWN);
	return attackWhenSitDownState;
}
State * Aladin::GetStopState()
{
	this->SetStateNumber(ALADIN_ANI_STOP);
	return stopState;
}
State * Aladin::GetThrowCherryInTheAirState()
{
	this->SetStateNumber(ALADIN_ANI_THROW_CHERRY_WHEN_IN_THE_AIR);
	return throwCherryInTheAirState;
}
State * Aladin::GetThrowCherryWhenStandState()
{
	this->SetStateNumber(ALADIN_ANI_THROW_CHERRY_WHEN_STANDING);
	return throwCherryWhenStandState;
}
State * Aladin::GetClimbTheLadderState()
{
	this->SetStateNumber(ALADIN_ANI_CLIMB_THE_LADDER);
	return climbTheLadderState;
}
State * Aladin::GetClimbTheRopeState()
{
	this->SetStateNumber(ALADIN_ANI_CLIMB_THE_ROPE);
	return climbTheRopeState;
}
State * Aladin::GetPlayWhenStandState()
{
	this->SetStateNumber(ALADIN_ANI_PLAY_WITH_CHERRY);
	return playWhenStandState;
}
void Aladin::Idle()
{
	state->Idle();
}

void Aladin::Walk()
{
	state->Walk();
}
void Aladin::Stop()
{
	state->Stop();
}
void Aladin::Jump()
{
	state->Jump();
}
void Aladin::JumpWhenPressing()
{
	state->JumpWhenPressing();
}
void Aladin::Attack()
{
	state->Attack();
}
void Aladin::AttackWhenSitDown()
{
	state->AttackWhenSitDown();
}
void Aladin::Falling()
{
	state->Falling();
}

void Aladin::SitDown()
{
	state->SitDown();
}
void Aladin::ThrowCherryInTheAir()
{
	state->ThrowCherryInTheAir();
}
void Aladin::ThrowCherryWhenStand()
{
	state->ThrowCherryWhenStand();
}
void Aladin::Climb()
{
	state->Climb();
}
void Aladin::PlayWhenStand()
{
	state->PlayWhenStand();
}
void Aladin::ActionWhenStand()
{
	state->ActionWhenStand();
}
void Aladin::TurnLeft()
{
	isLeft = true;
}
void Aladin::TurnRight()
{
	isLeft = false;
}

//Hàm trả về trạng thái nhân vật và camera ban đầu
void Aladin::Reset()
{
	this->SetPositionX(50);
	this->SetPositionY(200);
	Viewport::GetInstance()->Reset();
}

void Aladin::Update(DWORD dt)
{

	if(this->isActive==true)
		state->Update(dt);// gọi hàm cập nhật của aladin state
	//for (auto o : this->cherryList)
		//o->Update(dt);
}
void Aladin::Render()
{
	if(this->isActive==true)
		state->Render();//gọi hàm cập nhật của aladin state
	//for (auto o : this->cherryList)
		//o->Render();
}
