#include "Aladin.h"

vector<Animation *> Aladin::animations = vector<Animation *>();
Aladin *Aladin::__instance = NULL;

Aladin::Aladin()
{
	LoadResources();

	idleState = new AladinState(this, ALADIN_ANI_IDLE);
	walkState = new AladinState(this, ALADIN_ANI_WALK);
	stopState = new AladinState(this, ALADIN_ANI_STOP);
	jumpState = new AladinState(this, ALADIN_ANI_JUMP_NO_KEY);
	attackState = new AladinState(this, ALADIN_ANI_ATTACK);
	fallingState = new AladinState(this, ALADIN_ANI_FALLING_DOWN);
	actionWhenStandState = new AladinState(this, ALADIN_ANI_ACTION_WHEN_STAND);
	/*crouchState = new AladinState(this, ALADIN_ANI_CROUCH);
	throwShieldState = new AladinState(this, ALADIN_ANI_THROW_SHIELD);
	rollState = new AladinState(this, ALADIN_ANI_ROLL);
	kickState = new AladinState(this, ALADIN_ANI_KICK);
	standHitState = new AladinState(this, ALADIN_ANI_STAND_HIT);
	crouchHitState = new AladinState(this, ALADIN_ANI_CROUCH_HIT);
	sitOnShieldState = new AladinState(this, ALADIN_ANI_SIT_ON_SHIELD);
	swingState = new AladinState(this, ALADIN_ANI_SWING);
	wadeState = new AladinState(this, ALADIN_ANI_WADE);
	shieldUpState = new AladinState(this, ALADIN_ANI_SHIELD_UP);
	getHurtState = new AladinState(this, ALADIN_ANI_GET_HURT);
	deadState = new AladinState(this, ALADIN_ANI_DEAD);*/

	state = idleState;//trạng thái ban đầu cho aladin

	this->x = 60;
	this->y =300;
	//this->x = 0;
	//this->y = 0;
	this->width = ALADIN_SPRITE_WIDTH;
	this->height = ALADIN_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ALADIN_SPRITE_WIDTH;
	collider.height = ALADIN_SPRITE_HEIGHT;


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

	// ALADIN_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	/////ALADIN_ANI_WALK
	anim = new Animation(100);
	for (int i = 1; i < 13; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	/////ALADIN_ANI_STOP
	anim = new Animation(100);
	for (int i = 13; i < 22; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	////// ALADIN_ANI_JUMP_NO_KEY
	anim = new Animation(100);
	for (int i = 22; i < 33; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_JUMP_WITH_KEY
	anim = new Animation(100);
	for (int i = 33; i < 40; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_FALLING_DOWN
	anim = new Animation(100);
	for (int i = 40; i < 58; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_ATTACK
	anim = new Animation(100);
	for (int i = 58; i < 63; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_JUMP_WITH_KEY
	anim = new Animation(100);
	for (int i = 63; i < 70; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_CLIMB_LADDER
	anim = new Animation(100);
	for (int i = 70; i < 80; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_CLIMB_ROPE
	anim = new Animation(100);
	for (int i = 80; i < 90; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_ACTION_ON_THE_ROPE_WHEN_STOP
	anim = new Animation(100);
	for (int i = 90; i < 95; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_THROW_CHERRY_ON_THE_ROPE
	anim = new Animation(100);
	for (int i = 95; i < 100; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_ATTACK_ON_THE_ROPE
	anim = new Animation(100);
	for (int i = 100; i < 107; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_JUMP_OUT_FROM_THE_ROPE
	anim = new Animation(100);
	for (int i = 107; i < 116; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_PUSH
	anim = new Animation(100);
	for (int i = 116; i < 125; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//// ALADIN_ANI_ACTION_WHEN_STAND
	anim = new Animation(100);
	for (int i = 125; i < 132; i++)
	{
		Sprite * sprite = new Sprite(ALADIN_TEXTURE_LOCATION, listSprite[i], ALADIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
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
	this->SetStateNumber(ALADIN_ANI_WALK);
	return walkState;
}

State * Aladin::GetJumpState()
{
	this->SetStateNumber(ALADIN_ANI_JUMP_NO_KEY);
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
//State * Aladin::GetCrouchState()
//{
//	this->SetStateNumber(ALADIN_ANI_CROUCH);
//	return crouchState;
//}
//
//State * Aladin::GetThrowShieldState()
//{
//	this->SetStateNumber(ALADIN_ANI_THROW_SHIELD);
//	return throwShieldState;
//}
//
//State * Aladin::GetRollState()
//{
//	this->SetStateNumber(ALADIN_ANI_ROLL);
//	return rollState;
//}
//
//State * Aladin::GetKickState()
//{
//	this->SetStateNumber(ALADIN_ANI_KICK);
//	return kickState;
//}
//
//State * Aladin::GetStandHitState()
//{
//	this->SetStateNumber(ALADIN_ANI_STAND_HIT);
//	return standHitState;
//}
//
//State * Aladin::GetCrouchHitState()
//{
//	this->SetStateNumber(ALADIN_ANI_CROUCH_HIT);
//	return crouchHitState;
//}
//
//State * Aladin::GetSitOnShieldState()
//{
//	this->SetStateNumber(ALADIN_ANI_SIT_ON_SHIELD);
//	return sitOnShieldState;
//}
//
//State * Aladin::GetSwingState()
//{
//	this->SetStateNumber(ALADIN_ANI_SWING);
//	return swingState;
//}
//
//State * Aladin::GetWadeState()
//{
//	this->SetStateNumber(ALADIN_ANI_WADE);
//	return wadeState;
//}
//
//State * Aladin::GetShieldUpState()
//{
//	this->SetStateNumber(ALADIN_ANI_SHIELD_UP);
//	return shieldUpState;
//}
//
//State * Aladin::GetGetHurtState()
//{
//	this->SetStateNumber(ALADIN_ANI_GET_HURT);
//	return getHurtState;
//}
//
//State * Aladin::GetDeadState()
//{
//	this->SetStateNumber(ALADIN_ANI_DEAD);
//	return deadState;
//}

State * Aladin::GetStopState()
{
	this->SetStateNumber(ALADIN_ANI_STOP);
	return stopState;
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

void Aladin::Attack()
{
	state->Attack();
}
void Aladin::Falling()
{
	state->Falling();
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

	/*if (this->GetSpeedX() < 0 && this->GetPositionX() < 0)
	{
		this->SetPositionX(0);
	}
	if (this->GetPositionX() >= Game::GetInstance()->GetTiledMap()->GetInstance()->GetWidth() - 50)
	{
		this->SetPositionX(Game::GetInstance()->GetTiledMap()->GetInstance()->GetWidth() - 50);
	}*/
	if (this->GetPositionY() <= 0)
	{
		//this->SetPositionX(0);
		//this->SetPositionY(0);
	}
	state->Update(dt);// gọi hàm cập nhật của aladin state
	//shield->Update(dt);
}
void Aladin::Render()
{
	state->Render();//gọi hàm cập nhật của aladin state
	//shield->Render();// gọi hàm cập nhật của shield
}
